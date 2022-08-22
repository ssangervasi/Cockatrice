import { createStore, applyMiddleware } from 'redux';
import thunk from 'redux-thunk';

import rootReducer from './rootReducer';
import { RoomsState } from './rooms/rooms.interfaces';
import { ServerState } from './server/server.interfaces';

export interface RootState {
  rooms?: RoomsState;
  server?: ServerState;
}

const initialState: RootState = {};

const middleware: any = [thunk];

export const store = createStore(
  rootReducer,
  initialState,
  applyMiddleware(...middleware)
);
