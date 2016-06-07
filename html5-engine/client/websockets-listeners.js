import AnsiConverter from 'ansi-to-html';
import { log, hideConsole, updateGamesList } from './ui';

let ansiConverter = new AnsiConverter();

export const LISTENERS = {
    'error'(respond, stack) {
        log(ansiConverter.toHtml(stack), true);
    },
    
    'games:update'(respond, games) {
        updateGamesList(games.map(game => game.name));
    },

    'ev:game:compile-start'(respond, { name, rootPath }) {
        log(`Started compiling ${name} in ${rootPath}...`, true);
    },

    'ev:game:compile-file'(respond, fileName) {
        log(`Compiling ${fileName}...`);
    },

    'ev:game:compile-done'(respond, source) {
        log('Compilation done!');
        hideConsole();
        console.log(source);
    }
};