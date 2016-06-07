import fs from 'fs';
import promisify from 'es6-promisify';
import browserify from 'browserify';
import babelify from 'babelify';
import es2015preset from 'babel-preset-es2015';
import { makePlugin } from './game-ast-transformer';

export const GAMES_DIR = process.env.GAMES_DIR;
if(!GAMES_DIR) {
    console.log('/!\\ Please set GAMES_DIR environment variable.');
    console.log('    eg. $ GAMES_DIR=/home/me/games ./run.sh');
    process.exit();
}

export async function getGameinfo(name) {
    let rootPath = GAMES_DIR+'/'+name;

    let stat = await promisify(fs.stat)(rootPath);
    if(!stat.isDirectory()) {
        throw new Error(`${rootPath} should be a directory!`);
    }

    let gameinfo = JSON.parse(await promisify(fs.readFile)(rootPath + '/gameinfo.json'));
    gameinfo.rootPath = rootPath;

    if(!gameinfo.name || !gameinfo.context) {
        throw new Error(rootPath+' must contain a gameinfo.json.');
    }

    return gameinfo;
}

export async function listGames() {
    let contents = await promisify(fs.readdir)(GAMES_DIR);

    let games = [];
    for(let content of contents) {
        games.push(await getGameinfo(content));
    }

    return games;
}

export function compileGame(gameinfo, progress = () => {}) {
    return new Promise((resolve, reject) => {
        let filename = gameinfo.name.replace(/\s/g, '-');

        browserify(gameinfo.rootPath, { debug: true })
            .transform(babelify, {
                sourceType: 'module',
                presets: [es2015preset],
                plugins: [makePlugin(gameinfo.name)]
            })
            .on('file', progress)
            .bundle()
            .on('error', reject)
            .on('end', () => resolve(filename))
            .pipe(fs.createWriteStream(`${__dirname}/../client/dist/${filename}.js`));
    });
}