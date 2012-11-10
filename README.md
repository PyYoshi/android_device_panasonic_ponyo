Cyanogenmod for P-01D
=====================

### 概要
P-01DのOSをCyanogenmod用に移植するプロジェクトです。 協力者は随時募集しています。

### 注意点
*   転んでも泣かないこと。
*   すべて自己責任です。

### 連絡
*   [DevRenax](https://twitter.com/DevRenax)宛にリプライしてください
*   If you want to contact me, Please reply to [DevRenax](https://twitter.com/DevRenax). I can speak a little English.

### ビルド方法

#### ビルド環境
*   Ubuntu 12.04 x64
*   Oracle JDK 6 x64

上記以外はノンサポでどうぞ

#### ビルドエラーやバグの報告時の注意
自分のビルド環境やエラーログを報告時に添付してください。

これが無い場合、基本的に返信はしません。

#### ビルド前に以下のリンクを読んで理解すること。
*  [Cyanogenmod Wiki](http://wiki.cyanogenmod.com/index.php?title=Main_Page)
*  [Version Control with Repo and Git](http://source.android.com/source/version-control.html)
*  [Android Debug Bridge](http://developer.android.com/tools/help/adb.html)
*  [Initializing a Build Environment](http://source.android.com/source/initializing.html)

#### Cyanogenmodのソースコードを取得 (CM9の場合)
	mkdir cyanogenmod; cd cyanogenmod
	repo init -u git://github.com/CyanogenMod/android.git -b ics
	cd .repo
	wget https://raw.github.com/CM4IS01/android_device_panasonic_ponyo/ics/local_manifest.xml
	cd ..
	repo sync
	
#### 必要なプロプライエタリファイルを取得・vendorツリーの生成
	cd cyanogenmod/device/panasonic/ponyo
	sh extract-files.sh
	sh setup-makefiles.sh
	
[QDevNet](https://developer.qualcomm.com/mobile-development/mobile-technologies/gaming-graphics-optimization-adreno/tools-and-resources)からICS用のドライバを取得してvendorツリーへ置く
	
#### Cyanogenmodのソースにパッチを当てる
	cd cyanogenmod
	sh device/panasonic/ponyo/run_patch.sh
	
#### Cyanogenmodに必要なファイルを取得する
	cd cyanogenmod/vendor/cm/
	sh get-prebuilts
	
#### ビルド
	cd cyanogenmod
	. build/envsetup.sh
	brunch cm_ponyo-eng 2>error.log
	
#### 2度目以降のビルドを高速化させる(Optional)
	export USE_CCACHE=1
	export CCACHE_DIR=任意のディレクトリ/CCACHE
	
をビルド前にやっておく

#### パッチの初期化
	repo forall -c git reset --hard
