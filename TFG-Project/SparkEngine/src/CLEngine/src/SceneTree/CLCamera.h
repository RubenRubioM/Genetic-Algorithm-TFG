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
 * @author Clover Games Studio
 * 
 */
 
#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include <memory>

#include "CLEntity.h"


namespace CLE {
    //! Clase para las camaras del motor
    //! En esta clase encontramos muchos metodo utiles para gestionar camaras en nuestro motor gráfico
    class CLCamera : public CLEntity {
        public:
            CLCamera() {};
            CLCamera(unsigned int);
            ~CLCamera() {};
            //! Asigna valores a la camara
            //! @param n Distancia al plano near
            //! @param f Distancia al plano far
            //! @param r Distancia al plano right
            //! @param l Distancia al plano right
            //! @param t Distancia al plano top
            //! @param b Distancia al plano bottom
            void SetCameraConfig(GLfloat n, GLfloat f, GLfloat r, GLfloat l, GLfloat t, GLfloat b);
            //! Activa o desactiva la proyección perspectiva
            //! @param b Valor para la camara perspectiva
            //! @note False hace que se active la camara en motor ortográfico
            void SetPerspective(bool b)     { perspective = b; };
            //! Asigna FOV a la camara
            //! @param f FOV de la camara
            void SetFOV(GLfloat f)          { fov = f; };
            //! Activa o desactiva la camara
            //! @param a Bool para cambiar el valor de activación
            void SetActive(bool a)          { active = a; };
            //! Asigna el target de la camara
            //! @param pos Posición donde debe mirar la camara
            void SetCameraTarget(glm::vec3 pos)      { cameraTarget = pos; };
            void SetCameraUp(glm::vec3 pos)      { cameraUp = pos; };
            //! Devuelve si la camara es perspectiva
            //! @returns perspective
            bool IsPerspective() const      { return perspective; };
            //! Devuelve si la camara esta activa
            //! @returns active
            bool IsActive() const           { return active; };
            //! Devuelve el target de la camara
            //! @returns cameraTarget
            glm::vec3 GetCameraTarget()      { return cameraTarget; };
            float GetCameraFov()      { return fov; };
            glm::vec3 GetCameraUp()         { return cameraUp; };
            void Draw(GLuint shaderID);
            void DrawDepthMap (GLuint shaderID);
            //! Metodo que calcula la matriz de proyección
            //! @returns glm::mat4 matriz projection que se almacenará en CLE::CLNode
            glm::mat4 CalculateProjectionMatrix();
            //! Calcula el frustrum
        private:
            GLfloat m_near = 0.1f;
            GLfloat m_far = 5000.0f;
            GLfloat right = 1280.0f;
            GLfloat left = 0;
            GLfloat top = 720.0f;
            GLfloat bottom = 0;
            GLfloat aspect = 1280.f / 720.0f;
            GLfloat fov = 70.0f;
            bool perspective { true };
            bool active { true };
            glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);;
            glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);;
    };
}