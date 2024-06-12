import React, { useEffect, useState } from 'react';
import config from '../config';
import FileList from './FileList';
import '../styles/App.css';

const WebSocketComponent = ({ onFileItemClick }) => {
    const [files, setFiles] = useState([]);

    useEffect(() => {
        const socket = new WebSocket(config.WebsocketUrl);

        socket.onmessage = function(event) {
            const newData = JSON.parse(event.data);
            setFiles(prevFiles => [...prevFiles, newData]);
        };

        return () => {
            socket.close();
        };
    }, []);

    return (
        <div className="websocket-container">
            <FileList files={files} onFileItemClick={onFileItemClick} />
        </div>
    );
};

export default WebSocketComponent;