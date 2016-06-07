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

    'ev:game:compile-done'(respond, filename) {
        log('Compilation done! I will try to ENTER() your game now.');

        // Instead of recv the source and eval()'ing it, we load the game via a script tag.
        // Otherwise, source maps are very badly supported.
        $('body').append(`<script src="http://localhost:3030/${filename}.js"></script>`);

        setTimeout(() => {
            hideConsole();
        }, 1500);
    }
};