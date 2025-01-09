import fetch from 'node-fetch';

export default async function handler(req, res) {
    const { path } = req.query; // Menangkap parameter path dari query
    const esp32Url = `http://192.168.186.139/${path}`; // Ganti dengan IP lokal ESP32 Anda

    try {
        const response = await fetch(esp32Url, {
            method: req.method,
            headers: { 'Content-Type': 'application/json' },
            body: req.method === 'POST' ? JSON.stringify(req.body) : null
        });
        const data = await response.text();
        res.status(200).send(data);
    } catch (error) {
        res.status(500).send('Error communicating with ESP32');
    }
}
