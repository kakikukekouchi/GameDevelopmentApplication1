#include "InputControl.h"
#include "DxLib.h"

//静的メンバ
char InputControl::now_key[D_KEYCODE_MAX] = {};//現在の入力情報
char InputControl::old_key[D_KEYCODE_MAX] = {};//前フレームの入力情報

//キー情報更新処理
void InputControl::Update()
{
	//前フレームの入力情報に、現在の入力情報をコピーする
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	//現在の入力情報を更新する
	GetHitKeyStateAll(now_key);
}

//キーの押下情報取得
//押し続けているか？
bool InputControl::GetKey(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == TRUE));
}
//おしたしゅんかんか？
bool InputControl::GetKeyDown(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == FALSE));
}
//はなしたしゅんかんか?  
bool InputControl::GetKeyUp(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) && (old_key[key_code] == TRUE));
}
//キーコードの範囲チェック
bool InputControl::CheckKeyCodeRange(int key_code)
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

