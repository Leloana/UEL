#include <cmath>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <cell/app.hpp>
#include <cell/cell.hpp>

static bool      cell_rule_default(u8 count);
static glm::vec3 cell_color_default(CellState state, u8 x, u8 y, u8 z);

static bool      cell_rule_6_8(u8 count);
static glm::vec3 cell_color_6_8(CellState state, u8 x, u8 y, u8 z);

static bool      cell_alive_rule_cloud(u8 count);
static bool      cell_dead_rule_cloud(u8 count);
static glm::vec3 cell_color_cloud(CellState state, u8 x, u8 y, u8 z);

static bool      cell_alive_rule_decay(u8 count);
static bool      cell_dead_rule_decay(u8 count);
static glm::vec3 cell_color_decay(CellState state, u8 x, u8 y, u8 z);

static constexpr glm::vec4 LIGHT_POS = {0.0f, 5.0f, 0.0f, 1.0f};

static const LifeRule DEFAULT_RULE = {
    cell_rule_default, cell_rule_default, cell_color_default, 5, 0.85
};

static const LifeRule SIX_EIGHT_RULE = {
    cell_rule_6_8,
    cell_rule_6_8,
    cell_color_6_8,
    2,
    0.70,
};
static const LifeRule CLOUD_RULE = {
    cell_alive_rule_cloud,
    cell_dead_rule_cloud,
    cell_color_cloud,
    2,
    0.5,
};
static const LifeRule DECAY_RULE = {
    cell_alive_rule_decay,
    cell_dead_rule_decay,
    cell_color_decay,
    5,
    0.65,
};

static struct {
    Life        life;
    glm::mat4x4 projection;
    LifeRule    life_rule = DEFAULT_RULE;
    bool        full_init = false;
    GLuint      position_buffer;
    GLuint      color_buffer;
    GLuint      element_buffer;
    usize       update_rate = 2;
    // GLuint      vertex_shader;
    // GLuint      fragment_shader;
    // GLuint      shader_program;
    // GLuint      VAO;
    // GLint       projection_location;
    // GLint       model_view_location;
    // GLint       vertex_position;
    // GLint       vertex_colour;
} app_state;

static void init_lightining(void) {
    const glm::vec4 ambient = {0.0f, 0.0f, 0.0f, 1.0f};
    const glm::vec4 diffuse = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(diffuse));

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

static inline void life_init() {
    if (app_state.full_init) {
        app_state.life.init_full_random(
            app_state.life_rule.state_count,
            app_state.life_rule.start_dead_chance
        );
    } else if (app_state.life.get_dimension() <= 44) {
        f64 dead_chance = app_state.life_rule.start_dead_chance * 0.7;
        app_state.life.init_full_random(
            app_state.life_rule.state_count, dead_chance
        );
    } else {
        f64 dead_chance = app_state.life_rule.start_dead_chance;
        app_state.life.init_center_random(
            app_state.life_rule.state_count, dead_chance
        );
    }
}

static void init_buffers() {
    // glGenVertexArrays(1, &app_state.VAO);
    // glBindVertexArray(app_state.VAO);

    glGenBuffers(1, &app_state.position_buffer);
    glGenBuffers(1, &app_state.color_buffer);
    glGenBuffers(1, &app_state.element_buffer);

    // glBindVertexArray(0);
}

static void delete_buffers() {
    // glDeleteVertexArrays(1, &app_state.VAO);
    glDeleteBuffers(1, &app_state.position_buffer);
    glDeleteBuffers(1, &app_state.color_buffer);
    glDeleteBuffers(1, &app_state.element_buffer);
}

void init(void) {
    srand(42);
    app_state.life.update_size(8);
    life_init();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // define a cor de fundo
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    init_lightining();
    init_buffers();

    app_state.projection =
        glm::perspective<f32>(glm::pi<f32>() / 4.0, ASPECT_RATIO, 0.1, 300.0);

    // compile_shader();
    // app_state.vertex_position =
    //     glGetAttribLocation(app_state.shader_program, "vertex_position");
    // app_state.vertex_colour =
    //     glGetAttribLocation(app_state.shader_program, "vertex_colour");
    // app_state.projection_location =
    //     glGetUniformLocation(app_state.shader_program, "projection");
    // app_state.model_view_location =
    //     glGetUniformLocation(app_state.shader_program, "model_view");

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(app_state.projection));
}

void deinit(void) {
    delete_buffers();
    // glDeleteShader(app_state.vertex_shader);
    // glDeleteShader(app_state.fragment_shader);
}

static void draw_scene(void) {
    f32 radius = app_state.life.get_dimension() * 2.1;

    f32 time  = glfwGetTime();
    f32 cam_x = std::sin(time / 5) * radius;
    f32 cam_y = app_state.life.get_dimension();
    f32 cam_z = std::cos(time / 5) * radius;

    glm::vec3 eye_pos(cam_x, cam_y, cam_z);
    glm::vec3 center(0.0, 0.0, 0.0);
    glm::vec3 up(0.0, 1.0, 0.0);

    auto view = glm::lookAt(eye_pos, center, up);

    auto [vertices, colors, indices] =
        app_state.life.draw(app_state.life_rule.cell_color);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));

    auto light_pos = LIGHT_POS;
    light_pos.x += app_state.life.get_dimension();
    light_pos.y += app_state.life.get_dimension();
    light_pos.z += app_state.life.get_dimension();
    glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(light_pos));

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, app_state.position_buffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(glm::vec3),
        vertices.data(),
        GL_STATIC_DRAW
    );
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, app_state.color_buffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        colors.size() * sizeof(glm::vec3),
        colors.data(),
        GL_STATIC_DRAW
    );
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app_state.element_buffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(GLuint),
        indices.data(),
        GL_STATIC_DRAW
    );

    f64 start = -((static_cast<f64>(app_state.life.get_dimension()) / 2) - 0.5);
    auto translate = glm::translate(view, {start, start, start});

    glLoadMatrixf(glm::value_ptr(translate));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display(GLFWwindow *window) {
    draw_scene();
}

void framebuffer_size(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void timer(size_t value) {
    if (value % app_state.update_rate == 0) {
        app_state.life.update(app_state.life_rule);
    }
}

void scroll(GLFWwindow *window, double xoffset, double yoffset) {
    if (yoffset == 0) {
        return;
    }

    if (yoffset > 0) {
        app_state.life.update_size(
            std::min(app_state.life.get_dimension() + 4, 100)
        );
    } else {
        app_state.life.update_size(
            std::max(app_state.life.get_dimension() - 4, 8)
        );
    }

    life_init();
}

void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) {
        return;
    }
    bool restart = false;
    switch (key) {
        case '1':
            app_state.life_rule = DEFAULT_RULE;
            restart             = true;
            app_state.full_init = false;
            break;
        case '2':
            app_state.life_rule = SIX_EIGHT_RULE;
            restart             = true;
            app_state.full_init = false;
            break;
        case '3':
            app_state.life_rule = CLOUD_RULE;
            restart             = true;
            app_state.full_init = true;
            break;
        case '4':
            app_state.life_rule = DECAY_RULE;
            restart             = true;
            app_state.full_init = true;
            break;
        case GLFW_KEY_EQUAL:
            if (mods & GLFW_MOD_SHIFT) {
                app_state.update_rate =
                    std::max(app_state.update_rate / 2, static_cast<usize>(1));
            }
            break;
        case GLFW_KEY_MINUS:
            app_state.update_rate =
                std::min(app_state.update_rate * 2, static_cast<usize>(512));
            break;
        case GLFW_KEY_ENTER:
            restart = true;
            break;
        default:
            break;
    }
    if (restart) {
        life_init();
    }
}

static bool cell_rule_default(u8 count) {
    return count == 4;
}

static glm::vec3 cell_color_default(CellState state, u8 x, u8 y, u8 z) {
    f32 t = 0.0;
    switch (state) {
        case 1:
            t = 0.90;
            break;
        case 2:
            t = 0.60;
            break;
        case 3:
            t = 0.30;
            break;
        case 4:
            t = 0.09;
            break;
        default:
            break;
    }

    return {1.0, t, 0};
}

static bool cell_rule_6_8(u8 count) {
    return count >= 6 && count <= 8;
}

static inline f32 euclidian_distance_from_center(f32 x, f32 y, f32 z) {
    f32 dx     = x - static_cast<f32>(app_state.life.get_dimension() >> 1);
    f32 dy     = y - static_cast<f32>(app_state.life.get_dimension() >> 1);
    f32 dz     = z - static_cast<f32>(app_state.life.get_dimension() >> 1);
    f32 square = dx * dx + dy * dy + dz * dz;
    return std::sqrt(square);
}

static glm::vec3 cell_color_6_8(CellState state, u8 x, u8 y, u8 z) {
    f32 distance = euclidian_distance_from_center(x, y, z);
    f32 t        = distance / app_state.life.get_max_distance();

    return {0.1, 1 - t, t};
}

static bool cell_alive_rule_cloud(u8 count) {
    return count >= 13 && count <= 26;
}

static bool cell_dead_rule_cloud(u8 count) {
    return count == 13 || count == 14 || (count >= 17 && count <= 19);
}

static glm::vec3 cell_color_cloud(CellState state, u8 x, u8 y, u8 z) {
    glm::vec3 color;
    color[0] = static_cast<f32>(x) / app_state.life.get_dimension();
    color[1] = static_cast<f32>(y) / app_state.life.get_dimension();
    color[2] = static_cast<f32>(z) / app_state.life.get_dimension();
    return color;
}

static bool cell_alive_rule_decay(u8 count) {
    switch (count) {
        case 1:
        case 4:
        case 8:
        case 11:
            return true;
        default:
            return count >= 13 && count <= 26;
    }
}

static bool cell_dead_rule_decay(u8 count) {
    return count >= 13 && count <= 26;
}

static glm::vec3 cell_color_decay(CellState state, u8 x, u8 y, u8 z) {
    f32 distance = euclidian_distance_from_center(x, y, z);
    f32 t        = distance / app_state.life.get_max_distance();

    return {t * t, 0.0, 0.1};
}
