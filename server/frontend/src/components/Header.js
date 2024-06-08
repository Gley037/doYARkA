import Container from 'react-bootstrap/Container';
import Nav from 'react-bootstrap/Nav';
import Navbar from 'react-bootstrap/Navbar';

const Header = () => {
    return (
        <Navbar className='nav-blue-header'>
          <Container  className="ms-2">
            <Navbar.Brand href="#home" className="brand-bold">
              <img
                src="img/logo.png"
                width="55"
                height="55"
                className="d-inline mb-2"
              /> {''}
              <p className="d-inline ms-1">Do-YARkA-Analyser</p> 
            </Navbar.Brand>
          </Container>
          <Navbar.Brand className="brand-bold mb-2 pe-4">
            Android Intrusion Detection System
          </Navbar.Brand>
        </Navbar>
    );
};

export default Header;
