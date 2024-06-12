import React from 'react';
import { FileItem } from './FileItem';

const FileList = ({ files, onFileItemClick }) => {
    return (
        <ul className="file-list">
            {files.map((file, index) => (
                <FileItem key={index} file={file} onClick={() => onFileItemClick(file)} />
            ))}
        </ul>
    );
};

export default FileList;
