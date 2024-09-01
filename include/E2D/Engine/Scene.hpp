/**
 * @file Scene.hpp
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

#ifndef E2D_ENGINE_SCENE_HPP
#define E2D_ENGINE_SCENE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/ObjectRegistry.hpp>

#include <atomic>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

namespace e2d
{
struct Event;       // Forward declaration of Event
class SceneManager; // Forward declaration of SceneManager

/**
 * @class Scene
 * @ingroup engine
 * @brief Manages a collection of game objects and handles the lifecycle of a game scene.
 *
 * The `Scene` encapsulates all the logic and entities that make up a particular
 * section or state of the game. It manages the creation, update, and destruction of game objects,
 * handles input events, and renders the scene to the screen. Each `Scene` operates independently,
 * allowing the game engine to switch between different scenes seamlessly, such as switching
 * between a menu and gameplay.
 */
class E2D_ENGINE_API Scene : NonCopyable
{
    friend class Application;
    friend class SceneManager;

public:
    /**
     * @brief Pure virtual destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    virtual ~Scene() = 0;

    /**
     * @brief Gets the unique identifier of the Scene.
     *
     * Retrieves the unique identifier assigned to this scene.
     *
     * @return The identifier as a const reference to a string.
     */
    const std::string& getIdentifier() const;

    /**
     * @brief Creates and registers an object of type T.
     *
     * This method constructs an object of type T with the provided arguments and
     * registers it in the object registry. The object must derive from the base
     * class Object. If an object with the same identifier already exists in the
     * registry, an exception is thrown.
     *
     * @tparam T The type of the object to be created. Must derive from Object.
     * @tparam Args Variadic template parameter pack for the constructor arguments of T.
     * @param args Arguments to be forwarded to the constructor of T.
     * @return A reference to the newly created object of type T.
     * @throws std::runtime_error If an object with the same identifier already exists.
     */
    template <typename T, typename... Args>
    T& createObject(Args&&... args);

    /**
     * @brief Checks if the scene is currently loaded.
     *
     * This method returns whether the scene has been loaded. A loaded scene has its resources
     * allocated and is ready to handle events and updates.
     *
     * @return True if the scene is loaded, false otherwise.
     */
    bool isLoaded() const;

protected:
    /**
     * @brief Constructs a new Scene object.
     *
     * Initializes a new instance of the Scene class, generating a unique identifier for it.
     */
    Scene();

    /**
     * @brief Constructs an Scene with a given identifier.
     *
     * Initializes a new instance of the Scene class with the specified unique identifier.
     *
     * @param identifier A string representing the unique identifier of the scene.
     */
    explicit Scene(std::string identifier);

    /**
     * @brief Gets the SceneManager instance used by the application.
     *
     * This method returns the SceneManager that handles the current scenes within the application.
     *
     * @return A reference to the SceneManager.
     */
    SceneManager& getSceneManager() const;

    /**
     * @brief Called when the scene is loaded.
     *
     * This method is called when the scene is first created and loaded into the system.
     * Derived classes should override this method to perform any initialization or resource
     * allocation required when the scene is loaded.
     */
    virtual void onLoad();

    /**
     * @brief Called when the scene is unloaded.
     *
     * This method is called when the scene is removed from the manager or when the
     * application is shutting down. Derived classes should override this method to perform
     * any cleanup or resource deallocation required when the scene is unloaded.
     */
    virtual void onUnload();

private:
    /**
     * @brief Generates a unique identifier for the scene.
     *
     * This static method generates a unique identifier string that is used to uniquely
     * identify each scene instance. The identifier is based on an atomic counter and
     * is thread-safe due to the use of a mutex.
     *
     * @return A string representing the unique identifier of the scene.
     */
    static std::string generateUniqueIdentifier();

    /**
     * @brief Loads the scene, preparing it for use.
     *
     * This method loads the scene if it is not already loaded. It calls the `onLoad` method
     * to perform any necessary initialization and resource allocation required for the scene.
     * Once loaded, the scene is marked as ready for updates and rendering.
     */
    void load();

    /**
     * @brief Unloads the scene, freeing its resources.
     *
     * This method unloads the scene if it is currently loaded. It calls the `onUnload` method
     * to perform any necessary cleanup and resource deallocation. Once unloaded, the scene
     * will no longer be updated or rendered.
     */
    void unload();

    /**
     * @brief Handles incoming events for the scene.
     *
     * This method processes events that are directed at the scene, such as input events
     * or custom events. The method iterates over all registered objects in the scene,
     * allowing each to handle the event as needed.
     *
     * @param event The event to be handled by the scene.
     */
    void handleEvent(const Event& event);

    /**
     * @brief Performs fixed updates at a consistent rate.
     *
     * This method is called at a fixed interval (e.g., 60 times per second) to update
     * the state of the scene. Fixed updates are used for physics calculations and other
     * time-sensitive logic that requires consistent updates regardless of the frame rate.
     */
    void fixedUpdate();

    /**
     * @brief Performs variable updates based on elapsed time.
     *
     * This method is called as often as possible, typically every frame and is dependent on
     * the frame rate. It updates the scene based on the time elapsed since the last update,
     * allowing for smooth animations and time-based logic that scales with the frame rate.
     *
     * @param deltaTime The time elapsed since the last update, in seconds.
     */
    void variableUpdate(double deltaTime);

    /**
     * @brief Renders the scene's objects.
     *
     * This method is responsible for drawing all renderable objects within the scene.
     * It is called after the update phase to render the current state of the scene to the screen.
     */
    void draw();

    /**
     * @brief Cleans up objects that are no longer needed.
     *
     * This method removes objects that have been flagged for deletion from the scene,
     * freeing up memory and resources.
     */
    void clean();

    static std::atomic<std::uint64_t> s_counter; //!< Atomic counter used for generating unique scene identifiers.
    static std::mutex s_counterMutex;  //!< Mutex to ensure thread-safe access to the scene identifier counter.
    const std::string m_identifier;    //!< The unique identifier for this scene instance.
    bool              m_loaded{false}; //!< Flag indicating whether the scene is currently loaded.
    std::unique_ptr<ObjectRegistry> m_objectRegistry;        //!< Manages the lifecycle of objects within the scene.
    SceneManager*                   m_sceneManager{nullptr}; //!< Pointer to the SceneManager instance.

}; // Scene class

} // namespace e2d

#include <E2D/Engine/Scene.inl>

#endif //E2D_ENGINE_SCENE_HPP
