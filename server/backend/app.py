import json
import logging
import asyncio

from contextlib import asynccontextmanager
from fastapi import FastAPI, WebSocket, WebSocketDisconnect

from server.backend.scan.server import SocketHandler


log = logging.getLogger(__name__)

from functools import partial


@asynccontextmanager
async def lifespan(app: FastAPI):
    loop = asyncio.get_event_loop()
    
    callback = partial(socket_handler.handle_client,
                       websocket_clients=websocket_clients)

    loop.create_task(socket_handler.run_server(callback))
    log.info("Socket listener started")
    yield


websocket_clients = []
socket_handler = SocketHandler()
app = FastAPI(lifespan=lifespan)


@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    websocket_clients.append(websocket)
    try:
        while True:
            await websocket.receive_json()
    except WebSocketDisconnect:
        websocket_clients.remove(websocket)
