import React from 'react';
import {Navbar, Nav, Container, Offcanvas} from 'react-bootstrap'

const Sidebar = () => {
    return (
        <Navbar className='sidebar' bg='light' expand={true}>
            <Container fluid>
                <Navbar.Offcanvas
                        id='offcanvasNavbar'
                        aria-labelledby='offcanvasNavbarLabel'
                        placement='end'>
                    <Offcanvas.Body>
                        <Nav className='flex-column'>
                            <Nav.Item>Monitoring</Nav.Item>
                            <Nav.Link className='navlink'>Events</Nav.Link>
                            <Nav.Item>Management</Nav.Item>
                            <Nav.Link className='navlink'>Settings</Nav.Link>
                        </Nav>
                    </Offcanvas.Body>
                </Navbar.Offcanvas>
            </Container>
        </Navbar>
    );
};

export default Sidebar;
