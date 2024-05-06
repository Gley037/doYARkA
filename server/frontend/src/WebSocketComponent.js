import React, { useEffect, useState } from 'react';
import config from './config';
import './App.css';

const WebSocketComponent = () => {
    const [files, setFiles] = useState([]);

    useEffect(() => {
        const socket = new WebSocket(config.WebsocketUrl);

        socket.onmessage = function(event) {
            const data = JSON.parse(event.data);
            setFiles(data);
        };

        return () => {
            socket.close();
        };
    }, []);

    return (
        <div className="file-list">
            {files.map((file, index) => (
                <div key={index} className="file-item">
                    <p>Filename: {file.filename}</p>
                    <p>Rule: {file.rulename}</p>
                </div>
            ))}
        </div>
    );
};

export default WebSocketComponent;
