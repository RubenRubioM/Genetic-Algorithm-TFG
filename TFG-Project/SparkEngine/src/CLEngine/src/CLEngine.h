/**
 * Beast Brawl
 * Game created as a final project of the Multimedia Engineering Degree in the University of Alicante.
 * Made by Clover Games Studio, with members 
 * Carlos de la Fuente Torres delafuentetorresc@gmail.com,
 * Antonio Jose Martinez Garcia https://www.linkedin.com/in/antonio-jose-martinez-garcia/,
 * Jesús Mas Carretero jmasc03@gmail.com, 
 * Judith Mula Molina https://www.linkedin.com/in/judith-mm-18099215a/, 
 * Rubén Rubio Martínez https://www.linkedin.com/in/rub%C3%A9n-rubio-mart%C3%ADnez-938700131/, 
 * and Jose Valdés Sirvent https://www.linkedin.com/in/jose-f-valdés-sirvent-6058b5a5/ github -> josefrvaldes
 * 
 * 
 * @author Rubén Rubio Martínez <https://www.linkedin.com/in/rub%C3%A9n-rubio-mart%C3%ADnez-938700131/> 
 * 
 */
 
#pragma once

#ifndef CLENGINE_H
#define CLENGINE_H

#include <iostream>
#include <memory>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <SOIL2/SOIL2.h>

//Motor grafico
#include "SceneTree/CLNode.h"
#include "SceneTree/CLEntity.h"
#include "SceneTree/CLMesh.h"
#include "SceneTree/CLPointLight.h"
#include "SceneTree/CLCamera.h"
#include "SceneTree/CLShadowMapping.h"
#include "ResourceManager/CLResourceManager.h"

using namespace std;

namespace CLE {

//! Clase para iniciar el motor
class CLEngine {
    public:
        CLEngine() = default;

        CLEngine(const unsigned int, const unsigned int, const string);

        ~CLEngine();

        void SetVSync(bool);

        //! Activa o desactiva el test de profundidad.
        //! @param e Segun el bool lo activa o desactiva.
        void SetEnableDepthTest( bool e);

        //! Devuelve la ventana 
        //! @returns window La ventana de la aplicación
        GLFWwindow* GetWindow() const { return window; }

        //! Devuelve si la aplicación sigue corriendo 
        //! @returns bool del estado de la aplicación
        bool Run();

        //! Borra la pantalla
        void BeginScene();

        //! Dibuja todos los objetos del arbol
        void DrawObjects();

        //! Intercambio de buffers
        void EndScene();

        //! Asigna el titulo de la ventana
        //! @param title Titulo de la ventana
        void SetTitle(string&);

        //! Asigna el titulo de la ventana
        //! @param title Titulo de la ventana
        void SetTitle(string&&);

        //! Renderiza ImGui
        void RenderImgui();

        //! Actualiza el viewport
        void UpdateViewport();

        //! Devuelve el tiempo
        //! @returns time Tiempo de ejecucion
        double GetTime();

        //! Desactiva el cursor
        void DisableCursor();

        void CloseWindow();

        void PollEvents();

        void DrawDepthMap(const glm::mat4& lightSpaceMatrix);

        void RenderDepthMap(CLShadowMapping& shadowMap, CLResourceShader* depthShader, const glm::mat4& lightSpaceMatrix);

        void Clear();

        //! Devuelve el SceneManager
        //! @returns CLNode*
        //! @see CLE::CLNode()
        CLNode* GetSceneManager();

        //! Devuelve el ResourceManager
        //! @returns CLResourceManager*
        //! @see CLE::CLResourceManager()
        CLResourceManager* GetResourceManager();

        //! Devuelve la anchura de la pantalla
        //! @returns widht Anchura de la pantalla
        int GetScreenWidth() { return width; };

        //! Devuelve la altura de la pantalla
        //! @returns height Altura de la pantalla
        int GetScreenHeight() { return height; };

        //! Cambia el valor de la anchura de la pantalla
        //! @param w Anchura de la pantalla
        void SetScreenWidth(int w) { width = w; };
        
        //! Cambia el valor de la altura de la pantalla
        //! @param h Altura de la pantalla
        void SetScreenHeight(int h) { height = h; };
        
        //! Añade un shader al motor
        //! @param vertex Ruta del vertex shader
        //! @param fragment Ruta del fragment shader
        void AddShader(const string vertex, const string fragment);
        
        //! Añade un shader al motor
        //! @param vertex Ruta del vertex shader
        //! @param fragment Ruta del fragment shader
        //! @param geometry Ruta del geometry shader
        void AddShader(const string vertex, const string fragment, const string geometry);
        
        //! Añade un grupo a la escena
        //! @param id Identificador del nodo
        //! @returns CLE::CLNode()
        CLNode* AddGroup(CLNode* parent, unsigned int id);
       
        //! Añade una malla a la escena
        //! @param id Identificador del nodo
        //! @returns CLE::CLNode()
        CLNode* AddMesh(CLNode* parent,unsigned int id);
        
        //! Añade una malla a la escena
        //! @param id Identificador del nodo
        //! @param mesh Ruta de la malla
        //! @returns CLE::CLNode* 
        //! @see CLE::CLMesh()
        CLNode* AddMesh(CLNode* parent,unsigned int id,string mesh);
        
        //! Añade una luz puntual a la escena
        //! @param id Identificador del nodo
        //! @returns CLE::CLNode* 
        //! @see CLE::CLPointLight()
        CLNode* AddPointLight(CLNode* parent,unsigned int id);
        
        //! Añade una luz puntual a la escena
        //! @param id Identificador del nodo
        //! @param intensity Intensidad de la luz
        //! @param ambient Valor ambiente de la luz
        //! @param diffuse Valor difuso de la luz
        //! @param specular Valor especular de la luz
        //! @param constant Valor constante de la atenuación de la luz
        //! @param linear Valor lineal de la atenuación de la luz
        //! @param quadratic Valor cuadratico de la atenuación de la luz
        //! @returns CLE::CLNode* 
        //! @see CLE::CLPointLight()
        CLNode* AddPointLight(CLNode* parent,unsigned int id,glm::vec3 intensity, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
        
        //! Añade una camara a la escena
        //! @param id Identificador del nodo
        //! @returns CLE::CLNode* 
        //! @see CLE::CLCamera()
        CLNode* AddCamera(CLNode* parent,unsigned int id);
        
        //! Añade un sistema de particulas version **Punto**
        //! @param id Identificador del nodo
        //! @param nParticles Número de particulas
        //! @param velocity Vector de velocidad
        //! @param texture Ruta de la textura de la particula
        //! @param width Anchura de la particula
        //! @param height Altura de la particula
        //! @param spawnDelay Tiempo entre cada spawn de particula
        //! @param particlesToSpawn Particulas que se spawnean a la vez
        //! @param lifeSpan Vida de las particulas
        //! @param flags Mascara de bytes para aplicarle efectos
        //! @returns CLE::CLNode()
        //! @see CLE::CLParticleSystem()
        CLNode* AddParticleSystem(CLNode* parent,unsigned int id, unsigned int nParticles,glm::vec3 velocity,vector<string> textures,int width,int height,int spawnDelay,int particlesToSpawn,int lifeSpan, std::uint_fast8_t flags);
        
        //! Añade un sistema de particulas version **Linea, Cuadrado o Cubo**
        //! @param id Identificador del nodo
        //! @param nParticles Número de particulas
        //! @param velocity Vector de velocidad
        //! @param texture Ruta de la textura de la particula
        //! @param width Anchura de la particula
        //! @param height Altura de la particula
        //! @param spawnDelay Tiempo entre cada spawn de particula
        //! @param particlesToSpawn Particulas que se spawnean a la vez
        //! @param lifeSpan Vida de las particulas
        //! @param offset Dimensiones del objeto donde se spawnean las particulas
        //! @param orientation Orientacion de dicho spawner
        //! @param flags Mascara de bytes para aplicarle efectos
        //! @returns CLE::CLNode()
        //! @see CLE::CLParticleSystem()
        CLNode* AddParticleSystem(CLNode* parent,unsigned int id,unsigned int nParticles,glm::vec3 velocity,vector<string> textures,int width,int height,int spawnDelay,int particlesToSpawn,int lifeSpan,glm::vec3 offset, glm::vec3 orientation, std::uint_fast8_t flags);
        
        //! Añade un sistema de particulas version **Esfera**
        //! @param id Identificador del nodo
        //! @param nParticles Número de particulas
        //! @param velocity Vector de velocidad
        //! @param texture Ruta de la textura de la particula
        //! @param width Anchura de la particula
        //! @param height Altura de la particula
        //! @param spawnDelay Tiempo entre cada spawn de particula
        //! @param particlesToSpawn Particulas que se spawnean a la vez
        //! @param lifeSpan Vida de las particulas
        //! @param radious Radio de la esfera
        //! @param flags Mascara de bytes para aplicarle efectos
        //! @returns CLE::CLNode()
        //! @see CLE::CLParticleSystem()
        CLNode* AddParticleSystem(CLNode* parent,unsigned int id,unsigned int nParticles,glm::vec3 velocity,vector<string> textures,int width,int height,int spawnDelay,int particlesToSpawn,int lifeSpan,float radious, std::uint_fast8_t flags);
        
        //! Añade un sistema de particulas version **Circulo**
        //! @param id Identificador del nodo
        //! @param nParticles Número de particulas
        //! @param velocity Vector de velocidad
        //! @param texture Ruta de la textura de la particula
        //! @param width Anchura de la particula
        //! @param height Altura de la particula
        //! @param spawnDelay Tiempo entre cada spawn de particula
        //! @param particlesToSpawn Particulas que se spawnean a la vez
        //! @param lifeSpan Vida de las particulas
        //! @param radious Radio del circulo
        //! @param flags Mascara de bytes para aplicarle efectos
        //! @returns CLE::CLNode()
        //! @see CLE::CLParticleSystem()
        CLNode* AddParticleSystem(CLNode* parent,unsigned int id,unsigned int nParticles,glm::vec3 velocity,vector<string> textures,int width,int height,int spawnDelay,int particlesToSpawn,int lifeSpan,float radious,glm::vec3 orientation, std::uint_fast8_t flags);
        
        //! Añade un skybox a la escena
        //! @param right Textura right del cubo
        //! @param left Textura left del cubo
        //! @param top Textura top del cubo
        //! @param bottom Textura bottom del cubo
        //! @param front Textura front del cubo
        //! @param back Textura back del cubo
        //! @see CLE::CLSkybox()
        void AddSkybox(string right, string left, string top, string bottom, string front, string back);
        
        //! Añade la luz para usar shadow mapping
        //! @param lightId ID de del nodo de la luz a utilizar
        //! @see CLE::CLShadowMapping()
        void AddShadowMapping(GLuint lightId);
        
        //! Añade un billboard
        //! @param file Fichero de la textura
        //! @param vertically Parametro para poner vertical la textura
        //! @param width_ Anchura del billboard
        //! @param height Altura del billboard
        //! @returns CLE::CLNode()
        //! @see CLE::CLBillboard()
        CLNode* AddBillBoard(CLNode* parent,unsigned int id,string& file, bool vertically, float width_, float height_);
        
        //! Elimina un hijo de ese nodo
        //! @param child Puntero al hijo para eliminar
        //! @returns bool Si ha sido finalizado con exito o no
        bool RemoveChild(CLNode* child);
        
        //! Comprueba si tiene ese hijo
        //! @param child Puntero al hijo para comprobar
        //! @returns bool Si ha sido finalizado con exito o no
        bool HasChild(CLNode* child);
        
        //! Busca un nodo en el arbol por su ID
        //! @param id Identificador para buscar
        //! @returns CLNode* Puntero al nodo
        CLNode* GetNodeByID(unsigned int id);
        
        //! Busca el nodo respectivo en el arbol y te devuelve las dimensiones de su BoundingBox
        //! @param id Identificador para buscar
        //! @returns float tamanyo de lado del cuadrado
        float GetBoundingSizeById(unsigned int id);
        
        //! Elimina un hijo del arbol por su id
        //! @param id Identificador al hijo para eliminar
        //! @returns bool Si ha sido finalizado con exito o no
        bool DeleteNode(unsigned int id);
        
        //! Elimina un hijo del arbol por su dirección de memoria
        //! @param node Puntero al hijo para eliminar
        //! @returns bool Si ha sido finalizado con exito o no
        bool DeleteNode(CLNode* node);
        
        //! Dibuja el skybox
        void DrawSkybox();
        
        //! Devuelve la matriz view de la escena
        //! @returns view Matriz view de la escena
        static glm::mat4 GetViewMatrix()               { return view; }
        
        //! Devuelve la matriz projection de la escena
        //! @returns projection Matriz projection de la escena
        static glm::mat4 GetProjectionMatrix()         { return projection; }
        
        //! Devuelve la entidad de la camara activa
        //! @returns camera Camara activa en la escena CLE::CLCamera
        CLCamera* GetActiveCamera();
        
        //! Devuelve el nodo de la camara activa
        //! @returns camera Nodo de la camara activa en la escena
        CLNode*   GetActiveCameraNode();
        
        //! Devuelve las luces puntuales de la escena
        //! @returns pointLights Vector de luces puntuales de la escena
        vector<CLNode*> GetPointLights()              { return pointLights; };
        
        //! Devuelve las camaras de la escena
        //! @returns cameras Vector de camaras de la escena
        vector<CLNode*> GetCameras()            { return cameras; };
        
        //! Devuelve el ShadowMapping
        //! @returns shadowMapping Objeto CLE::CLShadowMapping
        static CLShadowMapping* GetShadowMapping()     {return shadowMapping.get();};
        
        //! Devuelve el objeto shader del shadowMapping
        //! @returns depthShdder Objeto CLE::CLResourceShader
        CLResourceShader* GetDepthShader()      {return depthShadder;};
        
        //! Devuelve el FOV de la camara
        //! @returns FOV Rango de vision de la camara
        float GetFovActualCamera();
        
        //! Devuelve la posicion a la que mira la camara
        //! @returns target Posicion a la que mira la camara
        glm::vec3 GetTargetActualCamera();
        
        //! Devuelve la posicion de la camara
        //! @returns target Posicion de la camara
        glm::vec3 GetPositionActualCamera();
        
        //! Dibuja una linea primitiva en 3D
        //! @param x1 X inicial
        //! @param y1 Y inicial
        //! @param z1 Z inicial
        //! @param x2 X final
        //! @param y2 Y final
        //! @param z2 Z final
        //! @param color Color de la linea
        //! @see CLE::CLColor()
        const void Draw3DLine(float x1, float y1, float z1, float x2, float y2, float z2,CLColor color) const;
        
        //! Dibuja una linea primitiva en 3D
        //! @param x1 X inicial
        //! @param y1 Y inicial
        //! @param z1 Z inicial
        //! @param x2 X final
        //! @param y2 Y final
        //! @param z2 Z final
        const void Draw3DLine(float x1, float y1, float z1, float x2, float y2, float z2) const;

        const void Draw3DLineLocal(CLNode* node, float x1, float y1, float z1, float x2, float y2, float z2) const;

        const void Draw3DLineLocal(CLNode* node, float x1, float y1, float z1, float x2, float y2, float z2, CLColor color) const;
        //const void DrawBoundingBoxOBB(CLEntity* entity, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 p5, glm::vec3 p6, glm::vec3 p7) const;
        
        //! Asigna la anchura de la linea
        void SetDrawLineWidth(int w) {lineWidth = w;};
        
        //! Elimina todas las luces y camaras de la escena
        void RemoveLightsAndCameras();
        
        //! Devuelve el nodo padre de la escena
        CLNode* GetRootNode() const { return smgr.get(); };
        
        //! Activa o desactiva las particulas
        //! @param mode Booleano para cambiar el modo
        void SetParticlesVisibility(bool mode);
        
        //! Activa o desactiva las vegetación
        //! @param mode Booleano para cambiar el modo
        void SetGrassActivate(bool mode) { grassActivate = mode; };
        
        void SetShadowsActivate(bool mode) { shadowsActivate = mode; };
        
        void ImGuiInit();
        
        void TerminateImGui();

    private:
        void CreateGlfwWindow(const unsigned int, const unsigned int, const string&);
        
        CLNode* GetNodeByIDAux(unsigned int id, CLNode* node, CLNode* root);
        
        //! Calcula las matriecs view y projection
        void CalculateViewProjMatrix(const glm::mat4& lightSpaceMatrix);
        
        //! Calcula las luces de la escena
        void CalculateLights();

        int width{};
        int height{};
        const string shaderVersion = "#version 450";
        GLFWwindow *window { nullptr };
        unsigned int hudShader { 0 };
        unsigned int textShader { 0 };
        vector<unsigned int> shaders;
        std::unique_ptr<CLNode> smgr {nullptr};
        std::unique_ptr<CLResourceManager> resourceManager {nullptr};
        GLuint VAOText, VBOText;
        bool grassActivate { true };
        bool shadowsActivate { false };
        inline static glm::mat4 projection;             // matriz proyeccion del modelo
        inline static glm::mat4 view;                   // matriz view del modelo
        GLuint shaderProgramID;
        int lineWidth = 1;
        inline static vector<CLNode*> pointLights;
        inline static vector<CLNode*> cameras;
        inline static GLuint debugShader = 0;
        inline static unique_ptr<CLSkybox> skybox = nullptr;
        inline static GLuint skyboxShader = 0;
        inline static GLuint billboardShader = 0;
        inline static unique_ptr<CLShadowMapping> shadowMapping = nullptr;
        inline static GLuint simpleDepthShader = 0;
        inline static CLResourceShader* depthShadder = nullptr;
        inline static GLuint particleSystemShader = 0;
};
}

#endif