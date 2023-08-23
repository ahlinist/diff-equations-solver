const handleFormInput = () => {
    const form = document.querySelector("form#equation-form");
    const a = form.querySelector("input[name='a']").value;
    const b = form.querySelector("input[name='b']").value;
    const c = form.querySelector("input[name='c']").value;
    const initialY = form.querySelector("input[name='initial-y']").value;
    const initialYPrime = form.querySelector("input[name='initial-y-prime']").value;

    const isInputValid = validateInput(a, b, c, initialY, initialYPrime);

    if (!isInputValid) {
        clearCanvas();
        return;
    }

    const url = new URL(window.location.protocol + "//" + window.location.host + "/second-order/solution");
    url.searchParams.append("a", a);
    url.searchParams.append("b", b || 0);
    url.searchParams.append("c", c || 0);
    url.searchParams.append("initial-y", initialY || 0);
    url.searchParams.append("initial-y-prime", initialYPrime || 0);
    
    fetch(url)
        .then(response => response.json())
        .then(response => {
            document.querySelector("div#initialEquation").textContent = response.initialEquation;
            document.querySelector("div#resultEquation").textContent = response.resultEquation;
            drawGraph(response.functionDataPoints);
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

    const maxAmplitude = data.reduce((max, obj) => {
        return obj.y > max ? obj.y : max;
      }, data[0].y);

    const maxTime = Math.max(...data.map(entry => entry.t));

    // Set the graph parameters
    const scaleX = Math.ceil(canvasWidth / (maxTime));
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
    const xAxisStep = calculateAxisStep(maxTime);

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

    for (const dataPoint of data) {
        const graphX = dataPoint.t * scaleX + offsetX;
        const graphY = -dataPoint.y * scaleY + offsetY;
        context.lineTo(graphX, graphY);
      }
    
    context.stroke();
}

const validateInput = (a, b, c, initialY, initialYPrime) => {
    const errorBox = document.querySelector("p#error-message");
    errorBox.innerHTML = "";

    let errorMessage = "";

    if (a <= 0) {
        errorMessage += "a should be greater than 0.<br>"
    }

    if (b < 0 || c < 0) {
        errorMessage += "b or c should be greater than or equal 0.<br>"
    }

    if ((!initialY || initialY == 0) && (!initialYPrime || initialYPrime == 0)) {
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
