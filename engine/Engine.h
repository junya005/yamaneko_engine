#pragma once

/// <summary>
/// ゲームエンジンの全コアモジュール（Application, Window, Time, Input, AssetManager, SceneManager, Config等）を一括インクルードするためのマスターヘッダーです。
/// </summary>
/// <remarks>
/// ゲーム側のソースファイルはこのヘッダーをインクルードするだけで、エンジンの全主要機能を利用できます。
/// <code>
/// #include "Engine.h"
/// 
/// class MyGame : public Engine::Application {
///     // ...
/// };
/// </code>
/// </remarks>

#include "Config.h"
#include "Time.h"
#include "Window.h"
#include "Renderer.h"
#include "TextRenderer.h"
#include "AssetManager.h"
#include "Input.h"
#include "UiWidget.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Application.h"
