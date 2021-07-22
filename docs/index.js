$(function() {
    "use strict";

    const header = $("#controls-header");
    const text = $("#controls-text");

    header.click(function() {
        if (text.is(":hidden")) {
            text.slideDown();
            header.removeClass("up");
        } else {
            text.slideUp();
            header.addClass("up");
        }
    });
});
