$(function() {
    "use strict";
    const tracks = [{"file": "oval.json", "description": "Oval-like track"},
                    {"file": "rectangle.json", "description": "Rectangular track"}];

    const track_sel_elm = $("#track-selection");

    tracks.forEach(track => {
        track_sel_elm.append(new Option(track.description, track.file));
    });

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
