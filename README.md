Cyanogenmod for P-01D
=====================

### 概要
P-01DのOSをCyanogenmod用に移植するプロジェクトです。 協力者は随時募集しています。

### 注意点
*   転んでも泣かないこと。
*   すべて自己責任です。
*   ビルドを行う場合はひと通り[Cyanogenmod Wiki](http://wiki.cyanogenmod.com/index.php?title=Main_Page)に目を通すこと。

### 連絡
*   [DevRenax](https://twitter.com/DevRenax)宛にリプライしてください
*   If you want to contact me, Please reply to [DevRenax](https://twitter.com/DevRenax). I can speak a little English.

### ビルド方法 (ビルドに必要なライブラリ等はインストール済みであるとする)

#### Cyanogenmodのソースコードを取得 (CM9の場合)
	mkdir cyanogenmod; cd cyanogenmod
	repo init -u git://github.com/CyanogenMod/android.git -b ics
	cd .repo
	wget https://raw.github.com/CM4IS01/android_device_panasonic_ponyo/ics/local_manifest.xml
	repo sync
	
#### 必要なプロプライエタリファイルを取得・vendorツリーの生成
	cd cyanogenmod/device/panasonic/ponyo
	sh extract-files.sh
	sh setup-makefiles.sh
	
[QDevNet](https://developer.qualcomm.com/mobile-development/mobile-technologies/gaming-graphics-optimization-adreno/tools-and-resources)からICS用のドライバを取得してvendorツリーへ置く
	
#### Cyanogenmodのソースにパッチを当てる
	cd cyanogenmod/device/panasonic/ponyo
	sh run_patch.sh
	
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
