using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FishingController : MonoBehaviour {

    [SerializeField] GirlsManager girlsManager;

    /// <summary>
    /// 接触した美女を判定し、スコアに加算する
    /// </summary>
    /// <param name="collision"></param>
    public void OnCollisionEnter2D(Collision2D collision)
    {
        // 接触したオブジェクトのタグを渡す
        girlsManager.GirlCounter(collision.gameObject.tag);

        // 接触したオブジェクトとルアーを非表示
        collision.gameObject.SetActive(false);
        this.gameObject.SetActive(false);

        // 減った分の女の子生成
        girlsManager.GirlSpawn();
    }
}