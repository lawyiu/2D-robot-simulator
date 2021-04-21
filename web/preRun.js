Module["preRun"].push(function() {
    "use strict";
    Module["addRunDependency"]("find_text_outputs");

    function findParentElms() {
        Module.serialOutElm = parent.document.getElementById('serial-console');
        Module.errorOutElm = parent.document.getElementById('error-console');
        Module["removeRunDependency"]("find_text_outputs");
    }

    if (/complete|interactive|loaded/.test(parent.document.readyState)) {
        findParentElms();
    } else {
        parent.document.addEventListener('DOMContentLoaded', findParentElms);
    }

    /* Workaround for bug where entering and exiting fullscreen will cause the canvas
       to be resized incorrectly. */
    window.devicePixelRatio = 1;

    document.addEventListener("keydown", function(event) {
       switch(event.code) {
           case "KeyR":
               Module["clearSerialOutput"]();
               break;
       }
       event.preventDefault();
    });
});
