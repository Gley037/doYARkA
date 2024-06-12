import React from 'react';

const FileInfoPanel = ({ file }) => {
    var hostname;
    if (file){
        hostname = file.agent_hostname ? file.agent_hostname : "Host";
    }

    return (
        <div className="file-info-panel bg-light">
            {file ? (
                <>
                    <div className="file-info-header">
                        <b>{file.filename}</b>
                        <p>Agent name: {hostname}</p>
                        <p>Agent address: {file.agent_ip}</p>
                        <p>Detection time: {file.time}</p>
                    </div>
                    <p>Rule: {file.rulename}</p>
                    <p>Description: {file.description}</p>
                    <p>Source: {file.src}</p>
                    <p>SHA256 file hash: {file.hash}</p>
                    <p>MITRE technic: {file.mitre}</p>
                </>
            ) : (
                <b>No file selected</b>
            )}
        </div>
    );
};

export default FileInfoPanel;