$(function() {
    "use strict";

    $(".console-header").click(function() {
        const header_elm = $(this);
        const collapse_elm = $("#" + header_elm.data("collapse-elm"));

        if (collapse_elm.is(":hidden")) {
            collapse_elm.slideDown();
            header_elm.removeClass("up");
        } else {
            collapse_elm.slideUp();
            header_elm.addClass("up");
        }
    });
});
