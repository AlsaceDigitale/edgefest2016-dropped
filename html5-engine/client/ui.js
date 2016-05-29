export const $HEADER = $('header');

export const $CANVAS = $('canvas#stage');

export let SIZE = 0;

export function scaleUi() {
    SIZE = $(window).height() - 100;
    $HEADER.width(SIZE);
    $CANVAS.width(SIZE).height(SIZE);
}