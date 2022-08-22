import * as _ from 'lodash';
import { createSelector } from 'reselect';

import { RootState } from 'store/store'

const selectRoomsState = (state: RootState) => state.rooms;
const selectRooms = createSelector([selectRoomsState], (state) => state.rooms);
const selectJoined = createSelector(
  [selectRoomsState],
  (state) => state.joined
);
const selectMessages = createSelector(
  [selectRoomsState],
  (state) => state.messages
);
const selectJoinedRooms = createSelector(
  [selectRooms, selectJoined],
  (rooms, joined) => _.filter(rooms, (room) => joined[room.roomId])
);
const selectSortGamesBy = createSelector(
  [selectRoomsState],
  (state) => state.sortGamesBy
);
const selectSortUsersBy = createSelector(
  [selectRoomsState],
  (state) => state.sortUsersBy
);
const selectRoom = createSelector(
  [selectRooms, (state, id) => id],
  (rooms, id: number) => _.find(rooms, ({ roomId }) => roomId === id)
);
const selectRoomMessages = createSelector(
  [selectMessages, (state, id) => id],
  (messages, id) => messages[id]
);
const selectRoomGames = createSelector([selectRoom], (room) => room.gameList);
const selectRoomUsers = createSelector([selectRoom], (room) => room.userList);

export const Selectors = {
  getRooms: selectRooms,
  getJoined: selectJoined,
  getMessages: selectMessages,
  getSortGamesBy: selectSortGamesBy,
  getSortUsersBy: selectSortUsersBy,
  getJoinedRooms: selectJoinedRooms,
  getRoom: selectRoom,
  getRoomMessages: selectRoomMessages,
  getRoomGames: selectRoomGames,
  getRoomUsers: selectRoomUsers,
};
