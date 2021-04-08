Module["preRun"].push(function() {
    var formElm = document.querySelector(".editor-form");
    var compileBtn = document.querySelector(".editor-form button");
    var compileOutput = document.querySelector("#compiler-console");

    function sendData(formData) {
        const XHR = new XMLHttpRequest;

        XHR.addEventListener("load", function(e) {
            const errMsg = XHR.status + ": " + XHR.statusText;

            if (XHR.status == 200) {
                const data = JSON.parse(XHR.responseText);

                if (data.errors == "") {
                    code = atob(data.bin);
                    FS.writeFile("/libcode.so", code);

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

        compileOutput.textContent = "Compiling...\n";

        const FD = new FormData(formElm);
        sendData(FD);
    });
});
