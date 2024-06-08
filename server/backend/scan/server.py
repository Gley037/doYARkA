import json
import socket
import asyncio
import datetime

from typing import List
from fastapi import WebSocket


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
        await self.send_to_clients(message, websocket_clients)


    async def get_client_info(self, client_ip: str):
        try:
            client_hostname = await asyncio.get_event_loop().run_in_executor(None, socket.gethostbyaddr, client_ip)
            client_hostname = client_hostname[0] if client_hostname else None
        except:
            client_hostname = None
            print("Failed to get client hostname")
        return client_hostname


    async def send_to_clients(self, data: str,
                              websocket_clients: List[WebSocket]):
        for agent in websocket_clients:
            agent_ip = f"{agent.client.host}:{agent.client.port}"
            agent_hostname = await self.get_client_info(agent_ip)

            message = json.loads(data)
            message["agent_ip"] = agent_ip
            message["agent_hostname"] = agent_hostname
            message["time"] = datetime.datetime.now().strftime("%Y-%B-%d %I:%M %p")

            await agent.send_text(json.dumps(message))


    async def run_server(self, callback):
        server = await asyncio.start_server(callback, self.ip, self.port)
        async with server:
            await server.serve_forever()
