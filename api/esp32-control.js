// api/esp32-control.js
export default async function handler(req, res) {
    const { method, query } = req;

    const ipESP32 = '192.168.186.139'; // IP ESP32 Anda di jaringan lokal

    if (method === 'POST') {
        const { led } = query;

        // Mengirimkan perintah ke ESP32 untuk mengubah status LED
        const response = await fetch(`http://${ipESP32}/${led}`, {
            method: 'POST',
        });

        const result = await response.text();
        res.status(200).send(result);
    } else {
        res.status(405).send('Method Not Allowed');
    }
}
