const handleFormInput = () => {
    const form = document.querySelector("form#equation-form");
    const a = form.querySelector("input[name='a']").value;
    const b = form.querySelector("input[name='b']").value;
    const c = form.querySelector("input[name='c']").value;
    const initialX = form.querySelector("input[name='initial-x']").value;
    const initialXPrime = form.querySelector("input[name='initial-x-prime']").value;
    const url = new URL(window.location.protocol + "//" + window.location.host + "/second-order/solution");
    url.searchParams.append("a", a || 0);
    url.searchParams.append("b", b || 0);
    url.searchParams.append("c", c || 0);
    url.searchParams.append("initial-x", initialX || 0);
    url.searchParams.append("initial-x-prime", initialXPrime || 0);
    
    fetch(url)
        .then(response => response.json())
        .then(data => {
            document.querySelector("div#initialEquation").textContent = data.initialEquation;
            document.querySelector("div#resultEquation").textContent = data.resultEquation;
            drawGraph(data.solution);
        })
        .catch(error => {
            console.error(error);
        });
}

const drawGraph = (solution) => {
    const canvas = document.getElementById('graphCanvas');
    const context = canvas.getContext('2d');
    
    const startRange = 0;
    const endRange = 17;
    
    // Clear the canvas
    context.clearRect(0, 0, canvas.width, canvas.height);
    
    // Set the graph parameters
    const scale = 20;
    const offsetX = 20;
    const offsetY = canvas.height / 2;
    
    // Draw the x and y axes
    context.beginPath();
    context.moveTo(0, offsetY);
    context.lineTo(canvas.width, offsetY);
    context.moveTo(offsetX, 0);
    context.lineTo(offsetX, canvas.height);
    context.strokeStyle = 'black';
    context.stroke();
    
    // Draw the function graph
    context.beginPath();
    context.strokeStyle = 'blue';
    
    const multiplier = solution.multiplier;
    const augend = solution.augend;
    const addend = solution.addend;

    for (let t = startRange; t <= endRange; t += 0.1) {
      const y = calculateFunctionValue(multiplier, augend, addend, t);
      const graphX = t * scale + offsetX;
      const graphY = -y * scale + offsetY;
      
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
