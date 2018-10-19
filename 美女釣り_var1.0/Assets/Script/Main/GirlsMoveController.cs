using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GirlsMoveController : MonoBehaviour {

    [SerializeField] float m_speed;

    private void Awake()
    {

    }

    // Use this for initialization
    void Start() {

    }

	// Update is called once per frame
	void Update () {

    }

    /// <summary>
    /// 美女が画面内を縦横無尽に動き回る
    /// </summary>
    /// <param name="direction">方向転換の方向</param>
    void BijoMove(float direction)
    {

    }

    public void OnCollitionHit()
    {
        var random = 0;

        // ランダムな値の角度を入れる
        random = Random.Range(0, 360);

        // 取得した角度に方向転換
        BijoMove(random);
    }
}