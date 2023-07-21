const handleFormInput = () => {
    const form = document.querySelector("form#equation-form");
    const a = form.querySelector("input[name='a']").value;
    const b = form.querySelector("input[name='b']").value;
    const c = form.querySelector("input[name='c']").value;
    const initialX = form.querySelector("input[name='initial-x']").value;
    const initialXPrime = form.querySelector("input[name='initial-x-prime']").value;

    const isInputValid = validateInput(a, b, c, initialX, initialXPrime);

    if (!isInputValid) {
        clearCanvas();
        return;
    }

    const url = new URL(window.location.protocol + "//" + window.location.host + "/second-order/solution");
    url.searchParams.append("a", a);
    url.searchParams.append("b", b || 0);
    url.searchParams.append("c", c || 0);
    url.searchParams.append("initial-x", initialX || 0);
    url.searchParams.append("initial-x-prime", initialXPrime || 0);
    
    fetch(url)
        .then(response => response.json())
        .then(data => {
            document.querySelector("div#initialEquation").textContent = data.initialEquation;
            document.querySelector("div#resultEquation").textContent = data.resultEquation;
            drawGraph(data);
        })
        .catch(error => {
            console.error(error);
        });
}

const drawGraph = (data) => {
    const canvas = document.getElementById('graphCanvas');
    const context = canvas.getContext('2d');
    clearCanvas(canvas);

    const canvasWidth = canvas.width;
    const canvasHeight = canvas.height;

    const solution = data.solution;
    const multiplier = solution.multiplier;
    const augend = solution.augend;
    const addend = solution.addend;
    const maxAmplitude = Math.max(
        Math.abs(calculateFunctionValue(multiplier, augend, addend, 0)),
        Math.abs(calculateFunctionValue(multiplier, augend, addend, data.maxAmplitudeExtremumAtT)),
    );

    const decaysAtT = data.decaysAtT;

    // Set the graph parameters
    const scaleX = Math.ceil(canvasWidth / (decaysAtT));
    const scaleY = Math.ceil(canvasHeight / (2 * maxAmplitude * 1.1));
    const offsetX = 20;
    const offsetY = canvasHeight / 2;
    
    // Draw the x and y axes
    context.beginPath();
    context.moveTo(0, offsetY);
    context.lineTo(canvasWidth, offsetY);
    context.moveTo(offsetX, 0);
    context.lineTo(offsetX, canvasHeight);
    context.strokeStyle = 'black';
    context.stroke();
    
    context.fillStyle = 'black'; // Set the fill color for the labels

    // Draw labels for x-axis
    const xAxisStep = calculateAxisStep(decaysAtT);

    for (let t = 0; t <= canvasWidth; t += xAxisStep) {
        const labelX = t * scaleX + offsetX;
        const labelY = offsetY + 12; //TODO: invoke once
        context.fillText(t, labelX, labelY);
    }

    // Draw labels for y-axis
    const yAxisStep = calculateAxisStep(maxAmplitude);
    const maxYValue = canvasHeight / 2;

    for (let y = -maxYValue; y <= maxYValue; y += yAxisStep) {
        const labelX = offsetX - 20; //TODO: invoke once
        const labelY = -y * scaleY + offsetY + 5;
        context.fillText(Math.round(y * 10000) / 10000, labelX, labelY);
    }

    // Draw the function graph
    context.beginPath();
    context.strokeStyle = 'blue';

    for (let t = 0; t <= canvasWidth; t += 0.1) {
      const y = calculateFunctionValue(multiplier, augend, addend, t);
      const graphX = t * scaleX + offsetX;
      const graphY = -y * scaleY + offsetY;
      
      context.lineTo(graphX, graphY);
    }
    
    context.stroke();
}

const calculateFunctionValue = (multiplier, augend, addend, t) => {
    const multiplierValue = calculateTerm(multiplier, t); 
    const augendValue = calculateTerm(augend, t);
    const addendValue = calculateTerm(addend, t);
    return multiplierValue * (augendValue + addendValue);
}

const calculateTerm = (term, t) => {
    if (term.type === "e") {
        return term.coefficient * Math.pow(Math.E, term.argument * t);
    }

    if (term.type === "sin") {
        return term.coefficient * Math.sin(term.argument * t);
    }

    if (term.type === "cos") {
        return term.coefficient * Math.cos(term.argument * t);
    }

    if (term.type === "t") {
        return term.coefficient * t;
    }
}

const validateInput = (a, b, c, initialX, initialXPrime) => {
    const errorBox = document.querySelector("p#error-message");
    errorBox.innerHTML = "";

    let errorMessage = "";

    if (a <= 0) {
        errorMessage += "a should be greater than 0.<br>"
    }

    if (b < 0 || c < 0) {
        errorMessage += "b or c should be greater than or equal 0.<br>"
    }

    if ((!initialX || initialX == 0) && (!initialXPrime || initialXPrime == 0)) {
        errorMessage += "x(0) and x'(0) can't be zero at the same time.<br>"
    }

    if (errorMessage) {
        errorBox.innerHTML = errorMessage;
        return false;
    } else {
        return true;
    }
}

const clearCanvas = (canvas) => {
    const context = canvas.getContext('2d');
    context.clearRect(0, 0, canvas.width, canvas.height);
}

const calculateAxisStep = (maxValue) => {
    const scaleFactor = 2.5;

    if (maxValue > scaleFactor) {
        const numberOfDigits = Math.trunc(maxValue/scaleFactor).toString().length;
        return Math.pow(10, numberOfDigits - 1);
    } else {
        const numberOfDigits = Math.trunc(scaleFactor/maxValue).toString().length;
        return Math.pow(10, -numberOfDigits);
    }
}
