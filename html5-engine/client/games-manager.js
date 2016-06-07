import three from 'three';
import easel from 'EaselJS';

// Expose libs and engine to the compiled games
window.__engine_import = { three, easel };
window.__engine_export = defineGameFunction;

const GAMES = {};

export function resetGame(game) {
    delete GAMES[game];
}

export function startGame(game) {
    console.log(JSON.stringify(Object.keys(GAMES[game])));
}

export function defineGameFunction(game, fnName, fn) {
    GAMES[game] || (GAMES[game] = {});
    GAMES[game][fnName] = fn;
}