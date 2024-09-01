/**
 * @file SceneManager.hpp
 *
 * MIT License
 *
 * Copyright (c) 2024 Emil Hörnlund
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef E2D_ENGINE_SCENE_MANAGER_HPP
#define E2D_ENGINE_SCENE_MANAGER_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <memory>
#include <vector>

namespace e2d
{
class Scene; // Forward declaration of Scene

/**
 * @class SceneManager
 * @ingroup engine
 * @brief Manages the lifecycle, transitions, and state of scenes in the engine.
 *
 * The `SceneManager` class is responsible for managing scenes within the game engine.
 * It maintains a stack of active scenes, supports scene transitions, and ensures that
 * scenes are properly loaded and unloaded. The SceneManager allows the game to move
 * between different states or levels, such as menus, gameplay, and settings.
 */
class E2D_ENGINE_API SceneManager final : NonCopyable
{
    friend class Application;

public:
    /**
     * @brief Constructs a new SceneManager object.
     *
     * Initializes a new instance of the SceneManager class, preparing it to manage scenes.
     */
    SceneManager();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~SceneManager();

    /**
     * @brief Checks if there are any active scenes.
     *
     * This method returns whether the SceneManager has any scenes currently loaded.
     * An empty SceneManager indicates that there are no active scenes in the application.
     *
     * @return True if no scenes are loaded, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Retrieves the currently active scene.
     *
     * This method returns a reference to the scene that is currently active. The active
     * scene is the one at the top of the scene stack. If no scenes are active, an exception
     * is thrown.
     *
     * @return A shared pointer to the currently active scene.
     * @throws std::runtime_error If no scenes are loaded.
     */
    const std::shared_ptr<e2d::Scene>& getActiveScene() const;

    /**
     * @brief Pushes a new scene onto the stack and makes it active.
     *
     * This method creates a new scene of type T, loads it, and pushes it onto the top
     * of the scene stack. The new scene becomes the active scene.
     *
     * @tparam T The type of the scene to be created. Must derive from `Scene`.
     * @tparam Args Variadic template parameters for the constructor arguments of T.
     * @param args Arguments to be forwarded to the constructor of T.
     * @return A reference to the newly created scene of type T.
     */
    template <typename T, typename... Args>
    T& pushScene(Args&&... args);

    /**
     * @brief Pops the current active scene off the stack.
     *
     * This method unloads and removes the scene at the top of the scene stack.
     * The scene below it (if any) becomes the new active scene. If no scenes are
     * loaded, an exception is thrown.
     *
     * @throws std::runtime_error If no scenes are loaded.
     */
    void popScene();

private:
    /**
     * @brief Cleans up unloaded scenes.
     *
     * This method removes scenes that have been unloaded from the scene manager,
     * freeing up resources associated with those scenes.
     */
    void clean();

    std::vector<std::shared_ptr<Scene>> m_scenes;         //!< Stack of active scenes managed by the SceneManager.
    std::vector<std::shared_ptr<Scene>> m_unloadedScenes; //!< List of scenes that have been unloaded but are not yet destroyed.

}; // SceneManager class

} // namespace e2d

#include <E2D/Engine/SceneManager.inl>

#endif //E2D_ENGINE_SCENE_MANAGER_HPP
