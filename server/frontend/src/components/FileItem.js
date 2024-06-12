import React from 'react';
import classNames from 'classnames';

export const FileItem = ({ file, onClick }) => {
    const warningClass = classNames('warning-label', {
        'level-1': file.level === "1",
        'level-2': file.level === "2",
        'level-3': file.level === "3",
    });

    const hostname = file.agent_hostname ? file.agent_hostname : "Host";

    return (
        <li>
            <div className="file-item" onClick={onClick}>
                <div className={warningClass}></div>
                <div className="file-details">
                    <p>{hostname} - {file.agent_ip}</p>
                    <p>Filename: {file.filename}</p>
                    <p>Rule: {file.rulename}</p>
                </div>
                <div className="file-item-time">{file.time}</div>
            </div>
        </li>
    );
};
