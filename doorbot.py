import requests
import time
import json
import os
import serial

class Telegram_Bot:
    def _init_(self):
        token = '5330145703:AAHo_OoOUkQhCNFju4Ud4xwI0BxFMwbtBSg'
        self.url_base = f'https://api.telegram.org/bot{token}/'
        

    def Start(self):
        update_id = None
        while True:
            atualizacao = self.get_new_messages(update_id)
            dados = atualizacao["result"]
            if dados:
                for dado in dados:
                    update_id = dado['update_id']
                    mensagem = str(dado["message"]["text"].lower())
                    usuario = str(dado["message"]["from"]["username"])
                    chat_id = dado["message"]["from"]["id"]
                    firstmessage = int(
                        dado["message"]["message_id"]) == 1
                    response = self.create_response(
                        mensagem, firstmessage)

                    #DEBUG
                    #print(dado)
                    ###########
                    print(usuario, chat_id, mensagem)
                    self.responder(response, chat_id)

    # Get messages
    def get_new_messages(self, update_id):
        link_requisicao = f'{self.url_base}getUpdates?timeout=100'
        if update_id:
            link_requisicao = f'{link_requisicao}&offset={update_id + 1}'
        resultado = requests.get(link_requisicao)
        return json.loads(resultado.content)

    # Create response
    def create_response(self, mensagem, firstmessage):
        message = None
        #arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
        
        if firstmessage == True or mensagem in ('/start', '/menu'):
            message = f'''        
             Hello, I'm your home security bot!{os.linesep}
            We're up for {os.linesep}
            Our current status is {os.linesep}
           
            Choose an option:{os.linesep}
                        
            /menu - Show this menu
            /status - Show status
            /log - Return logs
            /open - Open gate'''

        elif mensagem == ('/status'):
            message = f''' We're up for {uptime} and our current status is {status} '''

        elif mensagem == ('/log'):
            message = logs

        elif mensagem == ('/open'):
            arduino.write(bytes(x, 'utf-8'))
            message = ''' Gate opened sucessfully '''

        return message

    # Send response
    def responder(self, response, chat_id):
        link_requisicao = f'{self.url_base}sendMessage?chat_id={chat_id}&text={response}'
        requests.get(link_requisicao)

bot = Telegram_Bot()
bot.Start()