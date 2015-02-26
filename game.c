#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include "linmath.h"
#include "tux.h"
#include "helpers.h"
#include "game.h"
#include "my_errors.h"


int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
    
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
	
    
    glewExperimental = GL_TRUE;
    glewInit();
    GLuint vertexBuffer;
    //glGenBuffers(1, &vertexBuffer);
	
	glEnable(GL_DEPTH_TEST);
	
	
	
	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	
	GLuint texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL
	);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	
	GLuint vbo;
    glGenBuffers(1, &vbo);
    
    float vertices0[] = {
    //  Position		Color					Texcoords
        0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,		2.0f,  0.0f, // Top-right
       -0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,		0.0f,  0.0f, // Top-left
       -0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,		0.0f,  2.0f, // Bottom-left
        0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,		2.0f,  2.0f, // Bottom-right
    };
	
	
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		
		
		-2.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f,
		2.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f,
		2.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f,
		2.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f,
		-2.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f,
		-2.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f
	};
	
	for(int i = 0; i < 36; i++){
		//vertices[i*8+2] *= 2.0f;
		vertices[i*8+5] *= 2.0f;
		vertices[i*8+6] *= 2.0f;
		vertices[i*8+7] *= 2.0f;
	};
	
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint elements[] = {
        0, 1, 3,
        1, 2, 3,
    };
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    

    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shader_vert, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        glGetShaderInfoLog(vertexShader, 512, NULL, gl_err);
        fprintf(stderr, "!!---!!! SHADER ERROR !!---!!\n%s\n\n", gl_err);
        exit(-2);
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shader_frag, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){
        glGetShaderInfoLog(fragmentShader, 512, NULL, gl_err);
        fprintf(stderr, "!!---!!! SHADER ERROR !!---!!\n%s\n\n", gl_err);
        exit(-2);
    }
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                          8*sizeof(float), 0);
    
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                          8*sizeof(float), (void*)(3*sizeof(float)));
    
    GLint tex0Attrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(tex0Attrib);
    glVertexAttribPointer(tex0Attrib, 2, GL_FLOAT, GL_FALSE,
                          8*sizeof(float), (void*)(6*sizeof(float)));
    
    GLuint tex;
    glGenTextures(1, &tex);
	
	
    SDL_Surface* img = loadPNG_RW(tux_png, tux_png_len);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
    
    
    glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	
	GLint t = glGetUniformLocation(shaderProgram, "t");
	glUniform1f(t, 1.0f);
	float time;
    SDL_Event windowEvent;
	
	
	vec4 tmpv = {0.0f};
	mat4x4 tmpm = {0.0f};
	mat4x4 modal = {0.0f};
	mat4x4 scale = {0.0f};
	mat4x4 trans = {0.0f};
	mat4x4_identity(trans);
	mat4x4 away = {0.0f};
	mat4x4_identity(away);
	mat4x4_translate(away, -1.0f, -1.0f, 0.0f);
	mat4x4_translate(trans, 0.0f, 0.0f, 1.0f);
	mat4x4 rot = {0.0f};
	mat4x4 idnt = {0.0f};
	mat4x4_identity(idnt);
	mat4x4_scale_aniso(scale, idnt, 1.0f, 1.0f, -1.0f);
	mat4x4_rotate_Z(rot, idnt, E_PI);
	vec4 res = {1.0f, 0.0f, 0.0f, 1.0f};
	//mat4x4_mul_vec4(tmpv, modal, res);
	
	GLint uniModal = glGetUniformLocation(shaderProgram, "modal");
	
	mat4x4 view = {0.0f};
//	mat4x4_look_at(view, VEC(1.2f, 1.2f, 1.0f),
//						 VEC(0.0f, 0.0f, -0.0f),
//						 VEC(0.0f, 0.0f, 1.0f));
	mat4x4_look_at(view, VEC(1.0f, 1.0f, 1.0f),
						 VEC(0.0f, 0.0f, 0.0f),
						 VEC(0.0f, 0.0f, 1.0f));
	GLint uniView = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, *view);
	
	mat4x4 proj = {0.0f};
	mat4x4_perspective(proj, 45.0f, 8.0f/6.0f, 1.0f, 10.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, *proj);
	
	GLint uniColo;
	uniColo = glGetUniformLocation(shaderProgram, "colo");
	GLint uniRoto;
	uniRoto = glGetUniformLocation(shaderProgram, "roto");
	mat4x4 roto;
    while(true){
        if(SDL_PollEvent(&windowEvent)){
            if(windowEvent.type == SDL_QUIT) break;
        }
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		time = (float)clock() / (float)CLOCKS_PER_SEC;
		glUniform1f(t, sin(time * 2.0f * 3.14159265f * 10.0f));
		
		mat4x4_rotate_Z(rot, idnt, E_PI * time * 10.0f);
		mat4x4_mul(modal, away, rot);
		glUniformMatrix4fv(uniModal, 1, GL_FALSE, *modal);
		
		mat4x4_rotate_Z(roto, idnt, E_PI * time * -15.0f);
		glUniformMatrix4fv(uniRoto, 1, GL_FALSE, *idnt);
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
        glEnable(GL_STENCIL_TEST);
		
			// Draw floor
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilMask(0xFF);
			glDepthMask(GL_FALSE);
			glClear(GL_STENCIL_BUFFER_BIT);
			
			glUniformMatrix4fv(uniRoto, 1, GL_FALSE, *roto);
			glDrawArrays(GL_TRIANGLES, 36, 6);
			glUniformMatrix4fv(uniRoto, 1, GL_FALSE, *idnt);
			
			// Draw cube reflection
			glStencilFunc(GL_EQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthMask(GL_TRUE);
			
			mat4x4_mul(tmpm, trans, modal);
			mat4x4_mul(modal, scale, tmpm);
			glUniformMatrix4fv(uniModal, 1, GL_FALSE, *modal);
			
			glUniform3f(uniColo, 0.3f, 0.3f, 0.3f);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			glUniform3f(uniColo, 1.0f, 1.0f, 1.0f);
			
		glDisable(GL_STENCIL_TEST);
        
        SDL_GL_SwapWindow(window);
    }
    
    SDL_FreeSurface(img);
    
    glDeleteTextures(1, &tex);
    
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
	
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	
	glDeleteVertexArrays(1, &vao);
    
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}

int input_int(char* que){
  printf("%s\n", que);
  return 0;
}

int options_menu(char* que, char** ans, int ansNum){
  printf("%s\n", que);
  for(int i = 0; i < ansNum; i++){
    printf("%s\n", ans[i]);
  }
  int opt = input_int("What do you do?");
  return opt;
}