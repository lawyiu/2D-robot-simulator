(function() {
    "use strict";
    var simFrame = document.querySelector("#sim-frame");
    var formElm = document.querySelector(".editor-form");
    var compileBtn = document.querySelector(".editor-form button");
    var compileOutput = document.querySelector("#compiler-console");

    function base64ToUint8Array(base64) {
        var binary_string = window.atob(base64);
        var len = binary_string.length;
        var bytes = new Uint8Array(len);
        for (var i = 0; i < len; i++) {
            bytes[i] = binary_string.charCodeAt(i);
        }
        return bytes;
    }

    function sendData(formData) {
        const XHR = new XMLHttpRequest;

        XHR.addEventListener("load", function(e) {
            const errMsg = XHR.status + ": " + XHR.statusText;

            if (XHR.status == 200) {
                const data = JSON.parse(XHR.responseText);

                if (data.errors == "") {
                    var code = base64ToUint8Array(data.bin);
                    simFrame.contentWindow.Module.FS.writeFile("/libcode.so", code);

                    compileOutput.textContent += "Successfully compiled!\n" + data.errors;
                } else {
                    compileOutput.textContent += "Compilation Errors:\n" + data.errors;
                }
            } else {
                compileOutput.textContent += "Error occurred while contacting compile server: " + errMsg + "\n";
            }
        });

        XHR.addEventListener("error", function(e) {
            compileOutput.textContent += "Network error occurred while contacting compile server\n";
        });

        XHR.open("POST", "https://robot-sim-compiler.herokuapp.com/compile");
        XHR.send(formData);
    }

    compileBtn.addEventListener("click", function(e) {
        e.preventDefault();

        if (window.moduleReady) {
            compileOutput.textContent = "Compiling...\n";

            const FD = new FormData(formElm);
            sendData(FD);
        } else {
            compileOutput.textContent = "Simulator has not finished loading! Please try again when it is loaded.\n";
        }
    });
}());
