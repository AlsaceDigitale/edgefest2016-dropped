import { send } from './websockets';

export const $HEADER = $('header');
export const $SCREEN = $('#screen');
export const $CANVAS = $('canvas#stage');
export const $CONSOLE = $('pre#console');
export const $GAMESMENU = $('nav.games-menu');

export let SIZE = 0;

export function scaleUi() {
    SIZE = $(window).height() - 100;
    $HEADER.width(SIZE);
    $SCREEN.width(SIZE).height(SIZE);
}

export function log(message, server = false) {
    let type = server ? '<=' : '=>';
    message = message.replace(/\n/g, '\n   ');

    $CONSOLE.append(`<b>${type}</b> ${message}<br>`).slideDown(200);
}

export function hideConsole() {
    $CONSOLE.slideUp(200, () => $CONSOLE.html(''));
}

export function updateGamesList(gamesList) {
    $GAMESMENU.html('');
    
    for(let game of gamesList) {
        let $link = $(`<a>${game}</a>`).click(() => {
            send('game:compile', game);
            log(`Asking server to compile ${game}...`);
        });

        $GAMESMENU.append($link);
    }
}