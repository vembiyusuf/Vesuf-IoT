const endPoint = "http://192.168.186.139"; // Replace with your ESP32 IP address

// Function to toggle LED status
function toggleLed(button, ledId) {
    const img = document.querySelector(`img[alt='${ledId}']`);
    const statusText = button.previousElementSibling.querySelector(".status");

    // Send POST request to toggle LED
    fetch(`${endPoint}/${ledId}`, { method: "POST" })
        .then(response => response.text())
        .then(result => {
            if (result === "ON") {
                button.classList.remove("led-off");
                button.classList.add("led-on");
                button.textContent = "Matikan";
                img.src = "https://via.placeholder.com/150/00ff00"; // Green for ON
                statusText.textContent = "ON";
            } else {
                button.classList.remove("led-on");
                button.classList.add("led-off");
                button.textContent = "Nyalakan";
                img.src = "https://via.placeholder.com/150/ff0000"; // Red for OFF
                statusText.textContent = "OFF";
            }
        });
}

// Function to initialize LED status on page load
function initializeLedStatus(ledId, button) {
    const img = document.querySelector(`img[alt='${ledId}']`);
    const statusText = button.previousElementSibling.querySelector(".status");

    // Send GET request to get the current LED status
    fetch(`${endPoint}/${ledId}`, { method: "GET" })
        .then(response => response.text())
        .then(result => {
            if (result === "ON") {
                button.classList.remove("led-off");
                button.classList.add("led-on");
                button.textContent = "Matikan";
                img.src = "https://via.placeholder.com/150/00ff00"; // Green for ON
                statusText.textContent = "ON";
            } else {
                button.classList.remove("led-on");
                button.classList.add("led-off");
                button.textContent = "Nyalakan";
                img.src = "https://via.placeholder.com/150/ff0000"; // Red for OFF
                statusText.textContent = "OFF";
            }
        });
}

// Call this function for each LED card when the page is loaded
document.addEventListener("DOMContentLoaded", () => {
    // Loop through each LED card to initialize its state
    document.querySelectorAll("[alt^='led']").forEach((ledElement) => {
        const ledId = ledElement.getAttribute("alt");
        const button = ledElement.parentElement.querySelector("button");
        initializeLedStatus(ledId, button);  // Initialize LED status on page load
        button.addEventListener("click", () => toggleLed(button, ledId)); // Add event listener to toggle LED
    });
});
