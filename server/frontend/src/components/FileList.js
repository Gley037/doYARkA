import React from 'react';
import classNames from 'classnames';

const FileItem = ({ file, onClick }) => {
    const warningClass = classNames('warning-label', {
        'level-1': file.level === 1,
        'level-2': file.level === 2,
        'level-3': file.level === 3,
    });

    const hostname = file.agent_hostname ? file.agent_hostname : "Host";

    return (
        <li>
            <div className="file-item" onClick={onClick}>
                <div className={warningClass}></div>
                <div className="file-details">
                    <p>{hostname} - {file.client_ip}</p>
                    <p>Filename: {file.filename}</p>
                    <p>Rule: {file.rulename}</p>
                </div>
                <div className="file-item-time">{file.time}</div>
            </div>
        </li>
    );
};

const FileList = ({ files, onFileItemClick }) => {
    return (
        // <div className="sidebar">
        //     <div className="sidebar-sticky">
                <ul className="file-list">
                    {/* {files.map((file, index) => (
                        <FileItem key={index} file={file} onClick={() => onFileItemClick(file)} />
                    ))} */}
                     <li>
                        <div className="file-item">
                            <div className="warning-label level-3"></div>
                            <div className="file-details">
                                <p>DOMAIN\Director - 10.0.1.105</p>
                                <p>Filename: aboba</p>
                                <p>Rule: aboba</p>
                            </div>
                            <div className="file-item-time">2019-02-18 08:25:37</div>
                        </div>
                    </li>
                    <li>
                        <div className="file-item">
                            <div className="warning-label level-1"></div>
                            <div className="file-details">
                                <p>hostname-example - 192.168.1.13</p>
                                <p>Filename: example.txt</p>
                                <p>Rule: example-rule</p>
                            </div>
                            <div className="file-item-time">2019-02-18 08:25:37</div>
                        </div>
                    </li>
                    <li>
                        <div className="file-item">
                            <div className="warning-label level-3"></div>
                            <div className="file-details">
                                <p>hostname-example - 10.1.1.10</p>
                                <p>Filename: example.txt</p>
                                <p>Rule: example-rule</p>
                            </div>
                            <div className="file-item-time">2019-02-18 08:25:37</div>
                        </div>
                    </li>
                    <li>
                        <div className="file-item">
                            <div className="warning-label level-2"></div>
                            <div className="file-details">
                                <p>hostname-example - 192.168.1.1</p>
                                <p>Filename: example.txt</p>
                                <p>Rule: example-rule</p>
                            </div>
                            <div className="file-item-time">2019-02-18 08:25:37</div>
                        </div>
                    </li>
                    <li>
                        <div className="file-item">
                            <div className="warning-label level-1"></div>
                            <div className="file-details">
                                <p>hostname-example - 192.168.1.13</p>
                                <p>Filename: example.txt</p>
                                <p>Rule: example-rule</p>
                            </div>
                            <div className="file-item-time">2019-02-18 08:25:37</div>
                        </div>
                    </li>
                    <li>
                        <div className="file-item">
                            <div className="warning-label level-1"></div>
                            <div className="file-details">
                                <p>hostname-example - 192.168.1.13</p>
                                <p>Filename: example.txt</p>
                                <p>Rule: example-rule</p>
                            </div>
                            <div className="file-item-time">2019-02-18 08:25:37</div>
                        </div>
                    </li>
                    <li>
                        <div className="file-item">
                            <div className="warning-label level-1"></div>
                            <div className="file-details">
                                <p>hostname-example - 192.168.1.13</p>
                                <p>Filename: example.txt</p>
                                <p>Rule: example-rule</p>
                            </div>
                            <div className="file-item-time">2019-02-18 08:25:37</div>
                        </div>
                    </li>
                </ul>
            // </div>
        // </div>
    );
};

export default FileList;
