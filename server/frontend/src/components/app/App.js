import React, { useState } from 'react';
import Navbar from '../Header';
import FileInfoPanel from '../FileInfoPanel';
import WebSocketComponent from '../WebSocketComponent';
import Sidebar from '../Sidebar';
import '../../styles/App.css';

const App = () => {
  const [selectedFile, setSelectedFile] = useState(null);

  const handleFileItemClick = (file) => {
      setSelectedFile(file);
  };

  return (
      <div className="app-container">
          <Navbar />
          <div className="parent-container">
            <Sidebar/>
            <WebSocketComponent onFileItemClick={handleFileItemClick} />
            <FileInfoPanel file={selectedFile} />
          </div>
      </div>
  );
};

export default App;