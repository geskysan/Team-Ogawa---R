using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class GachaScript : MonoBehaviour {

    [SerializeField]
    Sprite[] lure;

    public class MyUtil
    {
        //渡された重み付け配列からIndexを得る
        public static int GetRandomIndex(params int[] weightTable)
        {
            var totalWeight = weightTable.Sum();
            var value = Random.Range(1, totalWeight + 1);
            var retIndex = -1;
            for (var i = 0; i < weightTable.Length; ++i)
            {
                if (weightTable[i] >= value)
                {
                    retIndex = i;
                    break;
                }
                value -= weightTable[i];
            }
            return retIndex;
        }
    }

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void clickGacha()
    {
        var weightTable = new int[]{
            70,
            28,
            2
        };
            int index1 = MyUtil.GetRandomIndex(70, 28, 2);
            Debug.Log("index1:" + index1);
        }
}
