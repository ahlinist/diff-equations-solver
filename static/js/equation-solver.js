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
        //.then(response => response.json())
        .then(response => response.text())
        .then(data => {
            document.querySelector("div#resultEquation").textContent = data;
        })
        .catch(error => {
            console.error(error);
        });
}
