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
});
