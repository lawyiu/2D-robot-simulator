(function() {
    "use strict";
    const selectElm = document.querySelector("#examples-selection");
    const progEditElm = document.querySelector("#program-editor");

    function addOption(selectElm, opStr, opVal) {
        var newOption = new Option(opStr, opVal);
        selectElm.appendChild(newOption);
    }

    function loadProgram(filename) {
        fetch("/examples/" + filename)
        .then(resp => resp.text())
        .then(data => {
            progEditElm.textContent = data;
        });
    }

    fetch("/examples/examples.json")
        .then(resp => resp.json())
        .then(data => {
            const examples = data.examples;
            for (let i in examples) {
                const example = examples[i];
                addOption(selectElm, example.file + " - " + example.description, example.file);
            }

            loadProgram(examples[0].file);
        });

    selectElm.addEventListener("change", function(event) {
        loadProgram(this.value);
    });
}());
