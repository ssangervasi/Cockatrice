#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QStyle>
#include <QMouseEvent>
#include "cardinfowidget.h"
#include "carditem.h"
#include "carddatabase.h"
#include "main.h"
#include "settingscache.h"

CardInfoWidget::CardInfoWidget(ResizeMode _mode, QWidget *parent, Qt::WindowFlags flags)
	: QFrame(parent, flags), pixmapWidth(160), aspectRatio((qreal) CARD_HEIGHT / (qreal) CARD_WIDTH), minimized(false), mode(_mode), info(0)
{
	cardPicture = new QLabel;
	cardPicture->setAlignment(Qt::AlignCenter);

	nameLabel1 = new QLabel;
	nameLabel2 = new QLabel;
	nameLabel2->setWordWrap(true);
	manacostLabel1 = new QLabel;
	manacostLabel2 = new QLabel;
	manacostLabel2->setWordWrap(true);
	cardtypeLabel1 = new QLabel;
	cardtypeLabel2 = new QLabel;
	cardtypeLabel2->setWordWrap(true);
	powtoughLabel1 = new QLabel;
	powtoughLabel2 = new QLabel;

	textLabel = new QTextEdit();
	textLabel->setReadOnly(true);

	QGridLayout *grid = new QGridLayout(this);
	int row = 0;
	grid->addWidget(cardPicture, row++, 0, 1, 2);
	grid->addWidget(nameLabel1, row, 0);
	grid->addWidget(nameLabel2, row++, 1);
	grid->addWidget(manacostLabel1, row, 0);
	grid->addWidget(manacostLabel2, row++, 1);
	grid->addWidget(cardtypeLabel1, row, 0);
	grid->addWidget(cardtypeLabel2, row++, 1);
	grid->addWidget(powtoughLabel1, row, 0);
	grid->addWidget(powtoughLabel2, row++, 1);
	grid->addWidget(textLabel, row, 0, -1, 2);
	grid->setRowStretch(row, 1);
	grid->setColumnStretch(1, 1);

	CardInfo *cardBack = db->getCard();
	setCard(cardBack);

	retranslateUi();
	setFrameStyle(QFrame::Panel | QFrame::Raised);
	setMinimumHeight(350);
	if (mode == ModeGameTab) {
		textLabel->setFixedHeight(100);
		setFixedWidth(sizeHint().width());
		setMaximumHeight(580);
	} else if (mode == ModePopUp)
		setFixedWidth(350);
	else
		setFixedWidth(250);
}

void CardInfoWidget::setCard(CardInfo *card)
{
	if (info)
		disconnect(info, 0, this, 0);
	info = card;
	connect(info, SIGNAL(pixmapUpdated()), this, SLOT(updatePixmap()));
	connect(info, SIGNAL(destroyed()), this, SLOT(clear()));

	updatePixmap();
	nameLabel2->setText(card->getName());
	manacostLabel2->setText(card->getManaCost());
	cardtypeLabel2->setText(card->getCardType());
	powtoughLabel2->setText(card->getPowTough());
	textLabel->setText(card->getText());
}

void CardInfoWidget::setCard(const QString &cardName)
{
	setCard(db->getCard(cardName));
}

void CardInfoWidget::setCard(AbstractCardItem *card)
{
	setCard(card->getInfo());
}

void CardInfoWidget::clear()
{
	setCard(db->getCard());
}

void CardInfoWidget::updatePixmap()
{
	QPixmap *resizedPixmap = info->getPixmap(QSize(pixmapWidth, pixmapWidth * aspectRatio));
	if (resizedPixmap)
		cardPicture->setPixmap(*resizedPixmap);
	else
		cardPicture->setPixmap(*(db->getCard()->getPixmap(QSize(pixmapWidth, pixmapWidth * aspectRatio))));
}

void CardInfoWidget::retranslateUi()
{
	nameLabel1->setText(tr("Name:"));
	manacostLabel1->setText(tr("Mana cost:"));
	cardtypeLabel1->setText(tr("Card type:"));
	powtoughLabel1->setText(tr("P / T:"));
}

void CardInfoWidget::resizeEvent(QResizeEvent * /*event*/)
{
	if ((mode == ModeDeckEditor) || (mode == ModeGameTab)) {
		pixmapWidth = qMin(width() * 0.95, (height() - 200) / aspectRatio);
		updatePixmap();
	}
}

void CardInfoWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if ((event->button() == Qt::MidButton) && (mode == ModePopUp))
		emit mouseReleased();
}
