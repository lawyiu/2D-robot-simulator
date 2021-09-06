Module["postRun"].push(function() {
    "use strict";
    var simFrame = parent.document.querySelector("#sim-frame");

    simFrame.width = document.body.scrollWidth;
    simFrame.height = document.body.scrollHeight;

    // Setup change event handler for track selection element
    const track_sel_elm = parent.document.querySelector("#track-selection");
    const app = Module.App.prototype.getInstance();

    track_sel_elm.addEventListener("change", function(e) {
        app.setCurrentLevel(this.value);
    });
});
