import { RootState } from 'store/store';

export const Selectors = {
  getInitialized: ({ server }: RootState) => server.initialized,
  getConnectOptions: ({ server }: RootState) => server.connectOptions,
  getMessage: ({ server }: RootState) => server.info.message,
  getName: ({ server }: RootState) => server.info.name,
  getVersion: ({ server }: RootState) => server.info.version,
  getDescription: ({ server }: RootState) => server.status.description,
  getState: ({ server }: RootState) => server.status.state,
  getUser: ({ server }: RootState) => server.user,
  getUsers: ({ server }: RootState) => server.users,
  getLogs: ({ server }: RootState) => server.logs,
  getBuddyList: ({ server }: RootState) => server.buddyList,
  getIgnoreList: ({ server }: RootState) => server.ignoreList,
};
