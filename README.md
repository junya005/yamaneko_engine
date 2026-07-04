# Template_GameDev_OpenGL

SDL2とOpenGLを用いたゲーム開発用のC++テンプレートリポジトリです。
CMakeとvcpkgを利用して、依存関係の管理とビルドを行います。

## 前提条件

- [Visual Studio 2022](https://visualstudio.microsoft.com/ja/vs/) (C++によるデスクトップ開発ワークロードがインストールされていること)
- [Git](https://git-scm.com/)
- [CMake](https://cmake.org/) (Visual Studioに同梱されているものでも可)

## セットアップ手順

本リポジトリでは `.gitignore` により、パッケージマネージャである `vcpkg` やサードパーティ製ライブラリのディレクトリ (`third_party`) が除外されています。そのため、リポジトリのクローン後に以下の手順で依存関係を手動でセットアップする必要があります。

### 1. リポジトリのクローン

コマンドプロンプトまたはPowerShellを開き、リポジトリをクローンしてディレクトリに移動します。

```bat
git clone https://github.com/YOUR_USERNAME/Template_GameDev_OpenGL.git
cd Template_GameDev_OpenGL
```
*(※リポジトリのURLはご自身の環境に合わせて変更してください)*

### 2. vcpkg のセットアップ

リポジトリ内に vcpkg をクローンし、ブートストラップスクリプトを実行して初期化します。

```bat
git clone https://github.com/microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
```

### 3. 依存ライブラリのインストール

vcpkg を使用して、本プロジェクトで必要なライブラリをインストールします。

```bat
.\vcpkg\vcpkg install sdl2 glad imgui[core,sdl2-binding,opengl3-binding] assimp opengl
```

### 4. サードパーティ・ライブラリ (third_party) のセットアップ

本プロジェクトでは、ヘッダーオンリーのアニメーションライブラリである `tweeny` を使用しています。
`third_party` ディレクトリを作成し、そこにリポジトリをクローンします。

```bat
mkdir third_party
cd third_party
git clone https://github.com/mobius3/tweeny.git
cd ..
```

### 5. プロジェクトのビルドと実行

1. Visual Studio 2022 を起動します。
2. 「ローカルフォルダーを開く (Open a local folder)」を選択し、クローンした `Template_GameDev_OpenGL` フォルダを選択します。
3. リポジトリに含まれている `CMakeSettings.json` が読み込まれ、自動的に vcpkg のツールチェーンファイルを使用した構成 (`Windows x64 (vcpkg)`) がセットアップされます。
4. CMakeのキャッシュ生成が完了したら、ツールバーから `Template_GameDev_OpenGL.exe` を選択し、スタートボタン（または `F5` キー）を押してビルドと実行を行います。

## 使用している主なライブラリ

- [SDL2](https://www.libsdl.org/) - ウィンドウ作成・入力処理
- [glad](https://glad.dav1d.de/) - OpenGL関数のローディング
- [Dear ImGui](https://github.com/ocornut/imgui) - デバッグ・ツール用GUI
- [Assimp](https://github.com/assimp/assimp) - 3Dモデル読み込み
- [OpenGL](https://www.opengl.org/) - グラフィックスAPI
- [tweeny](https://github.com/mobius3/tweeny) - トゥイーンアニメーション
