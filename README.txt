Nome: Chrystian Rocha

6 Filtros adicionados

Só 1 filtro é selecionado por vez

Selecionando o mesmo filtro novamente
 a imagem volta para a original

Filtros trabalham com flags de ativação booleanas


6 Stickers adicionados

Podem 1 ou mais filtros serem adicionados

Selecionando o mesmo filtro novamente
 o sticker desaparece, porém permanecem todos os outros 
	se estiverem ativados

Stickers trabalham num vetor de booleanos

vector objInitial 
contém a imagem original em tamanho original

vector objects
contém as miniaturas das imagens com os filtros adicionados para serem usados como botão de ativação

vector objShader
contém a lista de shader's para filtro

objSticker
contém a lista de stickers

listSticker
lista de booleanos para ativar os stickers

objMiniSticker
contém as miniaturas dos stickers para serem usados como botão de ativação

void SceneManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
função para capturar a posição do clique do mouse

Após o clique é feita uma verificação 
se o clique foi em algum dos botões
é ativada a respectiva flag

render()
desenha os botões
a imagem inicial

Verifica a listSticker
caso o valor na posição atual seja true
chama o objSticker[posição atual] que contém o sticker
Ele da um update e desenha o sticker na tela.