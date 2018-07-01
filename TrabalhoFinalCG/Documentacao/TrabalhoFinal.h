/** @file TrabalhoFinal.h
 *  @brief Declaração das funções para o programa TrabalhoFinal.
 *
 *  @author Grupo (ordem alfabética): Igor, Nathália & Yves
 */

/** @brief Funcionalidades do teclado, onde todas as funcionalidades e animações do programa serão feitas pelo teclado. As funcionalidades estão listadas em detalha na página inical da documentação.
 *
 *  @param key tecla pressionada pelo usuário
 *  @param x coordenada x do ponto atual
 *  @param y coordenada y do ponto atual
 *  @return Void
 */
void keyboardFunc(unsigned char key, int x, int y);


/** @brief Trata as quatro possibilidades de movimentos rotacionais (cima,baixo,esquerda,direita).
 *
 *  @param key tecla pressionada pelo usuário
 *  @param x coordenada x do ponto atual
 *  @param y coordenada y do ponto atual
 *  @return Void
 */
void rotKeyFunc(int key, int x, int y);


/** @brief As quatro funções: KeyUp, KeyDown, KeyLeft e KeyRight limitam a mudança de direção de rotação apenas com "reset".
 *  
 *  @return Void
 */
void KeyUp();


/** @brief As quatro funções: KeyUp, KeyDown, KeyLeft e KeyRight limitam a mudança de direção de rotação apenas com "reset".
 *  
 *  @return Void
 */
void KeyDown();


/** @brief As quatro funções: KeyUp, KeyDown, KeyLeft e KeyRight limitam a mudança de direção de rotação apenas com "reset".
 *  
 *  @return Void
 */
void KeyLeft();


/** @brief As quatro funções: KeyUp, KeyDown, KeyLeft e KeyRight limitam a mudança de direção de rotação apenas com "reset".
 *  
 *  @return Void
 */
void KeyRight();


/** @brief Restaura posição original e define rotação igual a zero.
 *  
 *  @return Void
 */
void ResetAnimation();


/** @brief Restaura posicao original e define rotação igual a zero.
 *  
 *  @return Void
 */
void ZeroRotation();


/** @brief Sombra, alterna entre GL_SMOOTH e GL_FLAT.
 *  
 *  @return Void
 */
void ShadeModelFunc();


/** @brief Preenchimento do poligono, alterna entre GL_LINE e GL_FILL.
 *  
 *  @return Void
 */
void FillModelFunc();


/** @brief Incrementa "u".
 *  
 *  @return Void
 */
void IncU();


/** @brief Decrementa "u".
 *  
 *  @return Void
 */
void DecU();


/** @brief Incrementa "u".
 *  
 *  @return Void
 */
void IncV();


/** @brief Decrementa "u".
 *  
 *  @return Void
 */
void DecV();


/** @brief Desenha superfícies/retalhos com todas suas especificações.
 *
 * @return Void
 */
void updateScene(void);


/** @brief Inicializa OpenGL (iluminação). 
 *
 *  @return Void
 */
void initRendering();


/** @brief Efetua mudança nas dimensões da janela (aumentando ou diminuindo de acordo com ação do mouse).
 *
 *  @param w tamanho da largura da janela
 *  @param h tamanho altura da janela
 *  @return Void
 */
void resizeWindow(int w, int h);

