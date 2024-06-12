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

        agent_peername = reader._transport.get_extra_info('peername')
        try:
            while True:
                agent_message = (await reader.readuntil(b'}')).decode('utf8')    
                if not agent_message:
                    break
                await self.send_to_clients(agent_message, agent_peername, websocket_clients)
        except:
            pass
        finally:
            writer.close()
            await writer.wait_closed()


    async def get_agent_info(self, agent_ip: str):
        try:
            agent_hostname = await asyncio.get_event_loop().run_in_executor(None, socket.gethostbyaddr, agent_ip)
            agent_hostname = agent_hostname[0] if agent_hostname else None
        except:
            agent_hostname = None
            print("Failed to get client hostname")
        return agent_hostname


    async def send_to_clients(self, data: str, agent_peername,
                              websocket_clients: List[WebSocket]):
        for client in websocket_clients:
            if agent_peername:
                agent_host = f"{agent_peername[0]}:{agent_peername[1]}"
                print(agent_host)
                agent_hostname = await self.get_agent_info(agent_peername[0])
                print(agent_hostname)

            message = json.loads(data)
            message["agent_ip"] = agent_host
            message["agent_hostname"] = agent_hostname
            message["time"] = datetime.datetime.now().strftime("%Y-%B-%d %I:%M %p")

            await client.send_text(json.dumps(message))


    async def run_server(self, callback):
        server = await asyncio.start_server(callback, self.ip, self.port)
        async with server:
            await server.serve_forever()
