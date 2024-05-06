import json
import socket
import asyncio

from typing import List
from fastapi import WebSocket
from functools import partial


class SocketHandler:
    def __init__(self):
        self.ip = socket.gethostname()
        self.port = 31337
        self.output_stream = asyncio.Queue()


    async def handle_client(self,
                            reader: asyncio.StreamReader,
                            writer: asyncio.StreamWriter, 
                            websocket_clients: List[WebSocket]):

        message = (await reader.read(-1)).decode('utf8')
        # message = json.loads(message)
        await self.send_to_clients(message, websocket_clients)


    async def send_to_clients(self, data: str,
                              websocket_clients: List[WebSocket]):
        for client in websocket_clients:
            await client.send_text(data)


    async def run_server(self, callback):
        server = await asyncio.start_server(callback, self.ip, self.port)
        async with server:
            await server.serve_forever()
