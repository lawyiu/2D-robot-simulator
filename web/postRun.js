Module["postRun"].push(function() {
    "use strict";
    var simFrame = parent.document.querySelector("#sim-frame");

    simFrame.width = document.body.scrollWidth;
    simFrame.height = document.body.scrollHeight;
});
