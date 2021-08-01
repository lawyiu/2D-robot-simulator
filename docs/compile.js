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

            switch (XHR.status) {
                case 200: {
                    const data = JSON.parse(XHR.responseText);
                    var code = base64ToUint8Array(data.bin);
                    const module = simFrame.contentWindow.Module;
                    module.FS.writeFile("/libcode.so", code);

                    compileOutput.textContent += "Successfully compiled!\n";

                    const restart_checkbox = $("#checkbox-restart");

                    if (restart_checkbox.prop("checked")) {
                        compileOutput.textContent += "Restarting simulation...\n";
                        const appInstance = module.App.prototype.getInstance();
                        appInstance.restart();
                    }
                    break;
                }

                case 400: {
                    const data = JSON.parse(XHR.responseText);
                    compileOutput.textContent += "Compilation Errors:\n" + data.errors;
                    break;
                }

                default: {
                    compileOutput.textContent += "Error occurred while contacting compile server: " + errMsg + "\n";
                    break;
                }
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
            FD.append("code", window.editor.getValue());
            sendData(FD);
        } else {
            compileOutput.textContent = "Simulator has not finished loading! Please try again when it is loaded.\n";
        }
    });
}());
