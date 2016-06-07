import { listGames, getGameinfo, compileGame } from './game-compiler';

export const LISTENERS = {
    async 'hello'(respond) {
        respond('games:update', await listGames());
    },

    async 'game:compile'(respond, gameName) {
        try {
            let gameinfo = await getGameinfo(gameName);
            respond('ev:game:compile-start', gameinfo);

            let source = await compileGame(gameinfo, file => respond('ev:game:compile-file', file));
            respond('ev:game:compile-done', source);
        } catch(err) {
            respond('error', err.stack);
        }
    }
};